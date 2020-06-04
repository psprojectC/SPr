import socket

HOST = '192.168.1.6'
PORT = 8101

if __name__ == '__main__':
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        data = s.recv(4096)
        print(data.decode('utf-8'))
        while True:
            choice = input('Your choice: ')
            if choice == '1':
                s.send(bytes('0', 'utf-8'))
                text = input('Input some text or -1 to cancel.')
                if text != '-1':
                    s.send(bytes(text, 'utf-8'))
            elif choice in ('2', '3', '4'):
                s.send(bytes(str(int(choice) - 1), 'utf-8'))
                resp = s.recv(4096)
                print(resp.decode('utf-16').rstrip('\x00'))
            elif choice == '5':
                s.send(bytes('5', 'utf-8'))
                break
            else:
                print('Invalid choice')
                s.send(bytes('-1', 'utf-8'))