import itertools
import os

MAX_GRID = 1000000
SIZE = 6

def generate_all_possible_boards():
    all_boards = []
    # Générer toutes les combinaisons possibles de la grille
    empty_cells = " " * SIZE * SIZE
    cnt = 0
    for combination in itertools.product("XO ", repeat=SIZE * SIZE):
        cnt += 1
        board = "".join(combination)
        if board.count("X") == board.count("O") or board.count("X") == board.count("O") + 1:
            all_boards.append(board)
            if (cnt > MAX_GRID):
                return all_boards
    return all_boards

if __name__ == "__main__":
    all_possible_boards = generate_all_possible_boards()

    datapath = os.path.join("data", f"dataset-{SIZE}.txt")
    with open(datapath, 'w') as f:
        f.write("\n".join(all_possible_boards))
