import numpy as np
from utils.types import Point


def calculate_euclidean_distance(u: Point, v: Point):
    dx = u.x - v.x
    dy = u.y - v.y

    return int(np.round(np.sqrt(dx*dx + dy*dy)))


def calculate_pseudo_euclidean_distance(u: Point, v: Point):
    dx = u.x - v.x
    dy = u.y - v.y

    real_distance = np.sqrt((dx*dx + dy*dy) / 10)
    rounded_distance = np.round(real_distance)

    if rounded_distance < real_distance:
        rounded_distance += 1

    return int(rounded_distance)