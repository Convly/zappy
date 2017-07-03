import argparse

def parser(argv):
    parser = argparse.ArgumentParser(add_help=False, description='AI binary for the Zappy project')
    parser.add_argument('-help', action='help', help='Display this help')
    parser.add_argument('-p', type=int, help='is the port number', required=True)
    parser.add_argument('-n', type=str, help='is the name of the team', required=True)
    parser.add_argument('-h', type=str, help='is the name of the machine; localhost by default', required=False, default='localhost')

    parsedArgs = parser.parse_args(argv)

    return (parsedArgs.p, parsedArgs.h, parsedArgs.n)