import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from time import ctime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


def is_integer(n):
    try:
        float(n)
    except ValueError:
        return False
    else:
        return float(n).is_integer()


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    grandtotal = 0.00
    currentcash = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    portfolio = db.execute(
        "SELECT * FROM shares JOIN coy ON shares.coy_id = coy.id WHERE user_id = ? ORDER BY coy_ticker", session["user_id"])
    coytickers = db.execute(
        "SELECT coy_ticker FROM coy WHERE id IN (SELECT coy_id FROM shares WHERE user_id = ?) ORDER BY coy_ticker", session["user_id"])
    for i in range(len(coytickers)):
        stock_value = lookup(coytickers[i]["coy_ticker"])
        portfolio[i]["price"] = stock_value["price"]
        portfolio[i]["totalprice"] = portfolio[i]["quantity"] * portfolio[i]["price"]
        grandtotal += stock_value["price"] * portfolio[i]["quantity"]
    time = ctime()
    return render_template("index.html", cash=currentcash[0]["cash"], time=time, portfolio=portfolio, grandtotal=grandtotal + currentcash[0]["cash"])


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
# Check for missing values
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide ticker", 400)
        elif not request.form.get("shares"):
            return apology("must provide number of shares", 400)

        ticker = request.form.get("symbol")
        stock_value = lookup(ticker)
        numberOfShares = request.form.get("shares")
        userinfo = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

# Check for inappropriate values
        if not stock_value:
            return apology("ticker does not exist", 400)
        elif not is_integer(numberOfShares):
            return apology("number of shares not available", 400)
        elif int(numberOfShares) <= 0:
            return apology("number of shares not available", 400)


# Check if user has enough balance
        paying = float(numberOfShares) * stock_value["price"]
        if paying > userinfo[0]["cash"]:
            return apology("not enough balance", 400)

# Check if coy exists in coy table
        if not db.execute("SELECT * FROM coy WHERE coy_ticker = ?", stock_value["symbol"]):
            db.execute("INSERT INTO coy (coy_name, coy_ticker) VALUES (?, ?)", stock_value["name"], stock_value["symbol"])
# Record quantity of shares bought by user from the share's coy into 'shares' table

        coyinfo = db.execute("SELECT id FROM coy WHERE coy_ticker = ?", stock_value["symbol"])

        if not db.execute("SELECT * FROM shares WHERE user_id = ? AND coy_id = ?", session["user_id"], coyinfo[0]["id"]):
            db.execute("INSERT INTO shares (user_id, coy_id, quantity) VALUES (?, ?, ?)",
                       session["user_id"], coyinfo[0]["id"], int(numberOfShares))
        else:
            currentshare = db.execute("SELECT * FROM shares WHERE user_id = ? AND coy_id = ?", session["user_id"], coyinfo[0]["id"])
            db.execute("UPDATE shares SET quantity = ? WHERE user_id = ? AND coy_id = ?",
                       currentshare[0]["quantity"] + int(numberOfShares), session["user_id"], coyinfo[0]["id"])
# Update user's cash balance in 'users' table
        db.execute("UPDATE users SET cash = ? WHERE id = ?", userinfo[0]["cash"] - paying, session["user_id"])
# Update user's transaction history
        db.execute("INSERT INTO transactions (user_id, coy_id, time, price, type, quantity) VALUES (?, ?, ?, ?, 'Buy', ? )",
                   session["user_id"], coyinfo[0]["id"], ctime(), stock_value["price"], int(numberOfShares))
        return redirect("/")

    else:
        balance = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        return render_template("buy.html", balance=balance)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    history = db.execute(
        "SELECT * FROM transactions JOIN coy ON transactions.coy_id = coy.id WHERE user_id = ? ORDER BY id DESC", session["user_id"])

    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("input field empty", 400)
        stock_value = lookup(symbol)
        if not stock_value:
            return apology("stock not found", 400)
        return render_template("quoted.html", stock_value=stock_value)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif not request.form.get("confirmation"):
            return apology("must provide password", 400)

        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) == 1:
            return apology("username already in use", 400)

        # Insert user and password hash into user table
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get(
            "username"), generate_password_hash(request.form.get("password")))

        # Reselect the user data from the user table for the id below
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        sellqty = request.form.get("shares")
        ticker = request.form.get("symbol")
# Check if user selected ticker
        if not ticker:
            return apology("did not select share", 400)
        stock_value = lookup(ticker)
# Check if ticker exists
        if not stock_value:
            return apology("Stock not available", 400)
# Check if user is holding share
        if not db.execute("SELECT * FROM shares WHERE user_id = ? AND coy_id = (SELECT id FROM coy WHERE coy_ticker = ?)", session["user_id"], stock_value["symbol"]):
            return apology("you do not own " + stock_value["symbol"] + " share", 400)
# Check if user has input into qty field
        if not sellqty:
            return apology("quantity field empty", 400)
# Check if user has input positive integer
        if not is_integer(sellqty):
            return apology("quantity unavailable", 400)
        if int(sellqty) == 0:
            return apology("quantity unavailable", 400)
# Check if user is selling correct qty ie sellqty<=shares.quantity
        userShare = db.execute("SELECT * FROM shares WHERE user_id = ? AND coy_id = (SELECT id FROM coy WHERE coy_ticker = ?)",
                               session["user_id"], stock_value["symbol"])
        sellqty = int(sellqty)
        if sellqty > userShare[0]["quantity"]:
            return apology("you don't have so many shares", 400)

# Record sale of share transaction
# Variable for ease of access
        coyinfo = db.execute("SELECT id FROM coy WHERE coy_ticker = ?", stock_value["symbol"])
        shareinfo = db.execute("SELECT quantity FROM shares WHERE coy_id = ?", coyinfo[0]["id"])
        userinfo = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
# Update quantity in shares table
        db.execute("UPDATE shares SET quantity = ? WHERE user_id = ? AND coy_id = ?", int(
            shareinfo[0]["quantity"]) - sellqty, session["user_id"], coyinfo[0]["id"])
# Update user's cash in users table
        db.execute("UPDATE users SET cash = ? WHERE id = ?", userinfo[0]
                   ["cash"] + sellqty * stock_value["price"], session["user_id"])
# Record transaction in transactions table
        db.execute("INSERT INTO transactions (user_id, coy_id, time, price, type, quantity) VALUES (?, ?, ?, ?, 'Sell', ? )",
                   session["user_id"], coyinfo[0]["id"], ctime(), stock_value["price"], sellqty)
# Remove row from shares table if quantity == 0
        if db.execute("SELECT quantity FROM shares WHERE user_id = ? AND coy_id = ?", session["user_id"], coyinfo[0]["id"])[0]["quantity"] == 0:
            db.execute("DELETE FROM shares WHERE user_id = ? AND coy_id = ?", session["user_id"], coyinfo[0]["id"])
        return redirect("/")
    else:
        coys = db.execute("SELECT coy_ticker FROM coy WHERE id IN (SELECT coy_id FROM shares WHERE user_id = ?)",
                          session["user_id"])
        return render_template("sell.html", coys=coys)
        

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)


@app.route("/search")
@login_required
def search():
    symbol = request.args.get("symbol")
    stock_value = lookup(symbol)
    stock_value["price"] = usd(stock_value["price"])
    stock_value["time"] = ctime()
    try:
        usershare = db.execute("SELECT * FROM shares WHERE user_id = ? AND coy_id = (SELECT id FROM coy WHERE coy_ticker = ?)",
                               session["user_id"], stock_value["symbol"])
        stock_value["quantity"] = usershare[0]["quantity"]
        return jsonify(stock_value)
    except:
        return jsonify(stock_value)