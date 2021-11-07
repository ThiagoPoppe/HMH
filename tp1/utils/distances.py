from typing import Tuple

import numpy as np

def euclidean2D_distance(u: Tuple, v: Tuple) -> int:
    du = u[0] - u[1]
    dv = v[0] - v[1]

    rounded_distance = np.round(np.sqrt(du**2 + dv**2))
    return int(rounded_distance)

def pseudo_eclidean2D_distance(u: Tuple, v: Tuple) -> int:
    du = u[0] - u[1]
    dv = v[0] - v[1]

    real_distance = np.sqrt((du**2 + dv**2) / 10)
    rounded_distance = np.round(real_distance)

    if rounded_distance < real_distance:
        return rounded_distance + 1

    return int(rounded_distance)