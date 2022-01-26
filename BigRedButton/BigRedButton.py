import re
import socket

class BigRedButton():
    def __init__(self, port, mac_address, proto=socket.BTPROTO_RFCOMM, timeout=None):
        """Creates an instance of BigRedButton and connects to specified `mac_address`."""
        self._mac_address = mac_address
        self._port = port
        self._proto = proto

        self._triggers = {}
        self._timeout = timeout
        self.connect()

    
    def create_socket(self):
        self.client = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, self._proto)
        self.client.settimeout(self._timeout)


    def connect(self):
        self.create_socket()
        while True:
            try:
                self.client.connect((self._mac_address, self._port))
            except OSError:
                pass
            except TimeoutError:
                print(f"Timeout at connection with {self._mac_address} by port {self._port}.")
            else:
                break


    def set_triggered_function(self, function_to_trigger: callable, string_trigger: str) -> bool:
        """Adds a triggereable function by a specific string."""
        try:
            if callable(function_to_trigger):
                self._triggers.update({string_trigger:function_to_trigger})
                return True
        except Exception:
            pass
        return False

    
    def run(self, debug=False):
        while True:
            try:
                data = self.client.recv(1024).decode()
                match = re.search(r"#(\w+)#", data)
                if match:
                    if debug:
                        print(data)
                    try:
                        self._triggers[match.group(0)]()
                    except KeyError as e:
                        pass


            except KeyboardInterrupt as e:
                self.client.close()