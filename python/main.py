import socket

HOST = ''                 # Symbolic name meaning all available interfaces
PORT = 8001            # Arbitrary non-privileged port
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)
while True:
    conn, addr = s.accept()
    data = conn.recv(1024)
    if not data: break
    print(data)
    distance = float(data)

    if distance > 1000 :
        import ctypes
        ctypes.windll.user32.LockWorkStation()
