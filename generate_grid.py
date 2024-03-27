import itertools
import os

SIZE = 3

def generate_all_possible_boards():
    all_boards = []
    # Générer toutes les combinaisons possibles de la grille
    empty_cells = " " * SIZE * SIZE
    for combination in itertools.product("XO ", repeat=SIZE * SIZE):
        board = "".join(combination)
        if board.count("X") == board.count("O") or board.count("X") == board.count("O") + 1:
            all_boards.append(board)
    return all_boards

if __name__ == "__main__":
    all_possible_boards = generate_all_possible_boards()

    datapath = os.path.join("data", f"dataset-{SIZE}.txt")
    with open(datapath, 'w') as f:
        f.write("\n".join(all_possible_boards))
