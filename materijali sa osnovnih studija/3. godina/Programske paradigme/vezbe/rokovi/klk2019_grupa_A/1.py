import json
import sys,re
import functools

def najtopliji(gradovi, min_temp, max_vlaznost):
    return list(filter( lambda x: x["temp"]> min_temp and x["vlaznost"]<max_vlaznost,gradovi))

def foo(x,y):
    if x["temp"] > y["temp"]:
        return -1
    elif x["temp"] < y["temp"]:
        return 1
    else:
        if x["vlaznost"] > y["vlaznost"]:
            return -1
        elif x["vlaznost"] < y["vlaznost"]:
            return 1
        else:
            return 0


with open(sys.argv[1]) as f:
    data = json.load(f)
    gradovi = najtopliji(data, 11, 90)
    sorted(gradovi, key = functools.cmp_to_key(foo) )
    for p in gradovi:
        print(p)