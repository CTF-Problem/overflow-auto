from flask import Flask, render_template, url_for, request, Response
import subprocess
import time

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')


if __name__ == '__main__':
    subprocess.Popen("./gotty --port 5001 --ws-origin '.*' -w nc overflow 5001", shell=True)
    app.run(debug=False, host='0.0.0.0', port=5000)
