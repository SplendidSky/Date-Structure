from irc.bot import *

if __name__ == "__main__":
    spec = ServerSpec('localhost')
    bot = SingleServerIRCBot((spec ,), 'bot', 'bot')
    bot.start()
