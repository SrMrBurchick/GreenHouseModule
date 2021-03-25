import os
import glob

#===============Config Settings =====================

config_file = "BuildConfig.mk"

CFG_PARAM_BOARD_FIELD = "BOARD"
CFG_PARAM_TARGET_FIELD = "MK_TARGET"

config_params = {
    CFG_PARAM_BOARD_FIELD : None,
    CFG_PARAM_TARGET_FIELD : None
}

#====================================================

stm32_boards = ["stm32f103"]

boards = stm32_boards

build_configs = [
    {
        CFG_PARAM_TARGET_FIELD : "STM32",
        CFG_PARAM_BOARD_FIELD : stm32_boards
    }
]

def board_select():
    print("Please select the board:")

    for board in boards:
        print("\t{} - {}".format(boards.index(board), board))

    board = int(input("Board: "))

    if board < len(boards):
        config_params[CFG_PARAM_BOARD_FIELD] = boards[board]
        for config in build_configs:
            if boards[board] in config[CFG_PARAM_BOARD_FIELD]:
                config_params[CFG_PARAM_TARGET_FIELD] =\
                        config[CFG_PARAM_TARGET_FIELD]
                break

        print(config_params)

    else:
        print("Error: invaid board id!")

        y = input("Do you want reselect? y/n: ")

        if "y" == y:
            board_select()

def change_config():
    buffer = []
    with open(config_file, "r") as config:
        for line in config.readlines():
            print(line)
            config_param = line[:line.find("=")]
            if config_param in config_params:
                buffer.append("{}={}".format(config_param,
                                             config_params[config_param]))
            else:
                buffer.append("{}=".format(config_param))

    print(buffer)

    with open(config_file, "w") as config:
        for line in buffer:
            config.write(line)
            config.write("\n")

if __name__ == "__main__":
    board_select()
    change_config()

