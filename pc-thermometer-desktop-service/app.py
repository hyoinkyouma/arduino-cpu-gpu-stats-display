import time
import serial
import temp_monitor as WinTmp
import sys

COMPORT = "COM7"
sys.setrecursionlimit(1500)

def get_cpu_temperature():
    data = []
    data.append(WinTmp.CPU_Temp())
    data.append(WinTmp.GPU_Temp())
    return data
            
def connect(COMPORT):
    try:
        ser = serial.Serial(COMPORT, 9600)
        print("Connected to " + COMPORT)
        time.sleep(2)
        ser.write(b'Connected')
        time.sleep(1)
        return ser
    except:
        print("Connection Error. Retrying in 3 seconds")
        time.sleep(3)
        return connect(COMPORT)

def send_data(con):
    data = get_cpu_temperature()
    print("CPU: " + str(data[0]) + " GPU: " + str(data[1]) + " CPU_CLK: " + str(round(WinTmp.CPU_CLK(), 1)) + " GPU_CLK: " + str(round(WinTmp.GPU_CLK(),1)))
    data_string = b"CPU: " +  bytes(str(round(data[0], 1)), 'utf-8') + b"," + b"GPU: " +  bytes(str(round(data[1], 1)), 'utf-8')  + b"CPU_CLK: " +  bytes(str(round(WinTmp.CPU_CLK(), 1)), 'utf-8') + b"GPU_CLK: " +  bytes(str(round(WinTmp.GPU_CLK(),1)) + " ", 'utf-8')
    con.write(data_string)
    print("Data sent")
    time.sleep(5)
    return True


if __name__ == "__main__":
    global CONN
    CONN = connect(COMPORT)
    while True:
        try:
            send_data(CONN)
        except:
            print("Disconnected sending data. Retrying in 3 seconds")
            CONN = connect(COMPORT)
