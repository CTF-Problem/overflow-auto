FROM python:3.11-slim

RUN apt update
RUN apt install netcat-traditional -y
RUN mkdir /app
WORKDIR /app
COPY ./requirements.txt /app/requirements.txt
RUN pip install --upgrade pip
RUN pip install -r requirements.txt

COPY ./templates /app/templates
COPY ./static /app/static
COPY ./app.py /app/app.py
COPY gotty /app/gotty

RUN adduser --disabled-password --gecos '' flask
RUN chown -R flask:flask /app
USER flask

CMD ["python", "app.py"]
