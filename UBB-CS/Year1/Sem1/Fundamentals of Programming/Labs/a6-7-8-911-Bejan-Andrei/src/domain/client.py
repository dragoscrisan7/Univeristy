class Client:

    def __init__(self, client_id, name):
        self._client_id = client_id
        self._name = name

    @property
    def client_id(self):
        return self._client_id

    @property
    def name(self):
        return self._name

    @client_id.setter
    def client_id(self, client_id):
        self._client_id = client_id

    @name.setter
    def name(self, name):
        self._name = name

# TODO test for client class
