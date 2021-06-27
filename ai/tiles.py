

class Tile:
    def __init__(self, player=0, food=0, linemate=0, deraumere=0, sibur=0, mendiane=0, phiras=0, thystame=0):
        self.player = player
        self.food = food
        self.linemate = linemate
        self.deraumere = deraumere
        self.sibur = sibur
        self.mendiane = mendiane
        self.phiras = phiras
        self.thystame = thystame
        self.coord = 0

    def __str__(self):
        return str([getattr(self, r) for r in Tile.__init__.__code__.co_varnames[1:]])
