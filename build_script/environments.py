class Environment:
    def __init__(self, path: str):
        self.path = path
        self.name = path.split('/')[-1]
