import datetime

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[96m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    INFORM = '\033[93m'

def setTime(payload):
    return '[' + datetime.datetime.now().strftime('%H:%M:%S') + ']: ' + payload

def adjustParams(payload, bold, underline):
    if bold: payload = bcolors.BOLD + payload
    if underline: payload = bcolors.UNDERLINE + payload
    return payload

def Warn(payload, bold=False, underline=False, end='\n'):
    payload = setTime(payload)
    payload = bcolors.WARNING + payload
    payload = adjustParams(payload, bold, underline)
    payload += bcolors.ENDC
    print(payload, end=end)

def Fail(payload, bold=False, underline=False, end='\n'):
    payload = setTime(payload)
    payload = bcolors.FAIL + payload
    payload = adjustParams(payload, bold, underline)
    payload += bcolors.ENDC
    print(payload, end=end)

def Head(payload, bold=False, underline=False, end='\n'):
    payload = setTime(payload)
    payload = bcolors.HEADER + payload
    payload = adjustParams(payload, bold, underline)
    payload += bcolors.ENDC
    print(payload, end=end)

def Inform(payload, bold=False, underline=False, end='\n'):
    payload = setTime(payload)
    payload = bcolors.INFORM + payload
    payload = adjustParams(payload, bold, underline)
    payload += bcolors.ENDC
    print(payload, end=end)

def Log(payload, bold=False, underline=False, end='\n', color='White'):
    payload = setTime(payload)    
    prefix = ''
    if color == 'Green': prefix = bcolors.OKGREEN
    elif color == 'Blue': prefix = bcolors.OKBLUE

    payload = prefix + payload
    payload = adjustParams(payload, bold, underline)
    payload += bcolors.ENDC
    print(payload, end=end)