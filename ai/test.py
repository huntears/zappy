##
## EPITECH PROJECT, 2021
## zappy_ai
## File description:
## test
##

from time import sleep

import client

cli = client.Client()
cli.connect("127.0.0.1", 42069)


@client.on_command(cmd="Team1", pop_cmd=False)
def some_func(cli: client.Client, msg: list) -> None:
    print("Team 1 return : " + str(msg))


@client.on_message(msg="dead")
def some_other_func(cli: client.Client, msg: list) -> None:
    print("Oh, I'm dead...")


@client.on_message(msg="WELCOME")
def welcome(cli: client.Client, msg: list) -> None:
    print("Got welcomed")
    cli.send("Team1")

cli.run()