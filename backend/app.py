from flask import Flask, request, jsonify, render_template
import subprocess
import os
import json

# Find the main project folder
BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# Locate frontend folders
FRONTEND_DIR = os.path.join(BASE_DIR, "frontend")

# Configure Flask
app = Flask(
    __name__,
    template_folder=os.path.join(FRONTEND_DIR, "templates"),
    static_folder=os.path.join(FRONTEND_DIR, "static")
)

# Choose the correct executable for the operating system
if os.name == "nt":
    ENGINE_PATH = os.path.join(BASE_DIR, "engine", "seeksy_api.exe")
else:
    ENGINE_PATH = os.path.join(BASE_DIR, "engine", "seeksy_api")


@app.route("/")
def home():
    return render_template("index.html")


@app.route("/analyze", methods=["POST"])
def analyze():

    try:
        data = request.get_json()

        disk_size = int(data["diskSize"])
        head_position = int(data["headPosition"])
        requests_list = data["requests"]

        # Prepare input for the C++ program
        input_data = (
            f"{disk_size} {head_position} {len(requests_list)} "
            + " ".join(map(str, requests_list))
        )

        # Run the C++ scheduling engine
        result = subprocess.run(
            [ENGINE_PATH],
            input=input_data,
            capture_output=True,
            text=True,
            timeout=10
        )

        if result.returncode != 0:
            return jsonify({"error": result.stderr.strip()}), 400

        # Convert C++ JSON output into Python data
        output_data = json.loads(result.stdout)

        return jsonify(output_data)

    except (KeyError, TypeError, ValueError):
        return jsonify({"error": "Invalid input data."}), 400

    except subprocess.TimeoutExpired:
        return jsonify({"error": "Scheduling engine timed out."}), 500

    except Exception as error:
        return jsonify({"error": str(error)}), 500


if __name__ == "__main__":
    app.run(
        host="0.0.0.0",
        port=int(os.environ.get("PORT", 5000)),
        debug=False
    )