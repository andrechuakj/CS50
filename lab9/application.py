import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        if db.execute("SELECT name FROM birthdays WHERE name LIKE (?)", name):
            return render_template("error.html", error = "Repeated name!")
        if not name:
            return render_template("error.html", error = "Missing name!")
        if not month or not day:
            return render_template("error.html", error = "Missing birthday!")
        try:
            int(month)
            int(day)
        except ValueError:
            return render_template("error.html", error = "Birthday format in numbers.")
        if name and month and day:
            db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)

        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays ORDER BY id DESC")
        return render_template("index.html", birthdays = birthdays)


@app.route("/edit", methods=["GET", "POST"])
def edit():
    if request.method == "POST":
        birthday_id = request.form.get("birthday_id")
        db.execute("DELETE FROM birthdays WHERE id = ?", birthday_id)
        return redirect("/edit")

    else:
        birthdays = db.execute("SELECT * FROM birthdays ORDER BY id DESC")
        return render_template("edit.html", birthdays = birthdays)


@app.route("/search")
def search():
    digit = request.args.get("q")
    if digit == "1":
        birthdays = db.execute("SELECT * FROM birthdays ORDER BY id DESC")
        return jsonify(birthdays)
    if digit == "2":
        birthdays = db.execute("SELECT * FROM birthdays ORDER BY id")
        return jsonify(birthdays)
    if digit == "3":
        birthdays = db.execute("SELECT * FROM birthdays ORDER BY name")
        return jsonify(birthdays)
    if digit == "4":
        birthdays = db.execute("SELECT * FROM birthdays ORDER BY name DESC")
        return jsonify(birthdays)
    if digit == "5":
        birthdays = db.execute("SELECT * FROM birthdays ORDER BY month, day")
        return jsonify(birthdays)
    if digit == "6":
        birthdays = db.execute("SELECT * FROM birthdays ORDER BY month DESC, day DESC")
        return jsonify(birthdays)

