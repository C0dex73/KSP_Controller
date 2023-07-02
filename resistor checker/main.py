"""
This module takes a number of buttons / levers
and return the value of the resistors to use
as well as all the possible values to detect more than one input pressed
"""

#resistors I have below 10K 
Resistors = [150,220,330,390,470,560,1000,1200,3300,4600]

def combinations(t:list[int]) -> list[int]:
    """Compute all final value possibilities of a set of resistors

    Args:
        t (list[int]): the set of resistors (in ohms)

    Returns:
        list[int]: all the posissibilities (in ohms)
    """
    r = []
    for id in range(len(t)+1):
        for subID in range(id+1, len(t)):
            tRes = 1/(1/t[id] + 1/t[subID])
            r.append(round(tRes))
    return r

def check(t:list[int]) -> int:
    """check for a set of resistors the smallest difference between two values in all the posible final values

    Args:
        t (list[int]): set of resistors to check

    Returns:
        int: smallest difference
    """
    for i in combinations(t):
        assert AssertionError("Not developped")
        
if __name__ == "__main__":
    assert AssertionError("No function called")