import serial
import json
import psycopg2
from psycopg2 import sql


ser = serial.serial_for_url('rfc2217://localhost:4000', baudrate=115200)
conn = psycopg2.connect(
    dbname="iot_sensors",
    user="postgres",
    password="postgrespw",
    host="localhost",
    port=55000
)


def insert_sensor_data_to_db(conn, sensor_id, temperature, humidity):
    with conn.cursor() as cur:
        insert_query = sql.SQL(
            """
            INSERT INTO sensor_data (sensor_id, temperature, humidity)
            VALUES (%s, %s, %s);
        """
        )
        cur.execute(insert_query, (sensor_id, temperature, humidity))
    conn.commit()


while True:
    line = ser.readline().decode("utf-8").strip()
    if not line:
        continue
    try:
        data = json.loads(line)
        for sensor in ["sensor1", "sensor2", "sensor3"]:
            if data[sensor]:
                insert_sensor_data_to_db(conn=conn,
                                         sensor_id=sensor,
                                         temperature=data[sensor]["temperature"],
                                         humidity=data[sensor]["humidity"])
        print("Данные записаны в БД")
    except json.JSONDecodeError:
        print(f"Ошибка парсинга: {line}")

