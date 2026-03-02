from flask import Flask, jsonify, render_template, request, redirect
import csv
import subprocess
import os

app = Flask(__name__)

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
DATA_FILE = os.path.join(BASE_DIR, "alpha_stream.csv")
INPUT_FILE = os.path.join(BASE_DIR, "market_events.csv")

DATA = []

def load_output():
    DATA.clear()
    if not os.path.exists(DATA_FILE):
        return
    with open(DATA_FILE, "r") as f:
        reader = csv.DictReader(f)
        for row in reader:
            DATA.append(row)

# -------- UI --------
@app.route("/")
def index():
    load_output()
    return render_template("index.html")

# -------- CSV UPLOAD --------
@app.route("/upload", methods=["POST"])
def upload():
    file = request.files.get("file")
    if not file:
        return redirect("/")

    file.save(INPUT_FILE)

    # Run C++ engine
    subprocess.run(
        ["./orderbook_engine"],
        cwd=os.path.join(BASE_DIR, "..", "..", "build"),
        check=True
    )

    load_output()
    return redirect("/")

# -------- API --------
@app.route("/event/<int:i>")
def event(i):
    if i < 0 or i >= len(DATA):
        return jsonify({"error": "index out of range"})
    return jsonify(DATA[i])

@app.route("/count")
def count():
    return jsonify({"count": len(DATA)})

if __name__ == "__main__":
    app.run(debug=True)
