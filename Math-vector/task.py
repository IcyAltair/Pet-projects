"""
Implement vector class that should make comparison of vectors by length.

>>> Vector([1, 2])
Vector([1, 2])

>>> Vector(1)
TypeError: expected Any[Tuple[Any[float, int]], List[Tuple[Any[float, int]]].

>>> Vector([[1]])
TypeError: expected Any[Tuple[Any[float, int]], List[Tuple[Any[float, int]]].

>>> Vector(["a"])
TypeError: expected Any[Tuple[Any[float, int]], List[Tuple[Any[float, int]]].

>>> Vector("a")
TypeError: expected Any[Tuple[Any[float, int]], List[Tuple[Any[float, int]]].

>>> Vector([1, 2]) > Vector([0, 1])
True

>>> Vector([1, 2]) >= Vector([2, 1])
True

>>> Vector([1, 2]) <= Vector([2, 1])
True

>>> Vector([1, 2, 3]) >= Vector([2, 1])
ValueError: vectors shape mismatch.

>>> Vector([1, 2]) == Vector([2, 1.00001])
True

Vectors are considered equal if the difference between their lengths <= EPSILON.
"""
from dataclasses import dataclass, InitVar
from math import sqrt
from typing import Any

EPSILON = 0.001


@dataclass
class Vector:
    """This is a class of math vector implementation.

    The main functionality of this class is comparison of vectors by length.

    Attributes:
        v (any): An object (tuple or list) of vector's values (int or float).
        desc (str): A string of vector's description.
        gen_desc (InitVar): An auto generated string of vector's description.
        v_len (float): Value of vector's length
        v_size (int): Value of quantity of vector's element

    """

    v: Any
    desc: str = ""
    gen_desc: InitVar[bool] = True
    v_len: float = 0
    v_size: int = 0

    def __post_init__(self, gen_desc: str):
        self.check_input(self.v)
        if gen_desc and self.desc == "":
            self.desc = "Created vector with values: " + \
                ", ".join(list(map(str, list(self.v))))

    def __eq__(self, other) -> bool:
        """Implementation of operator "==" between two vectors.

        Args:
            other (Vector): An object of class Vector.

        Returns:
            bool: Result of comparison in terms of "==" operator.

        Raises:
            ValueError: If vectors differ in size.

        """
        if self.v_size != other.v_size:
            raise ValueError("vectors shape mismatch.")
        return abs(self.v_len - other.v_len) <= EPSILON

    def __ne__(self, other) -> bool:
        """Implementation of operator "!=" between two vectors.

        Args:
            other (Vector): An object of class Vector.

        Returns:
            bool: Result of comparison in terms of "!=" operator.

        Raises:
            ValueError: If vectors differ in size.

        """
        if self.v_size != other.v_size:
            raise ValueError("vectors shape mismatch.")
        return abs(self.v_len - other.v_len) > EPSILON

    def __lt__(self, other) -> bool:
        """Implementation of operator "<" between two vectors.

        Args:
            other (Vector): An object of class Vector.

        Returns:
            bool: result of comparison in terms of "<" operator.

        Raises:
            ValueError: If vectors differ in size.

        """
        if self.v_size != other.v_size:
            raise ValueError("vectors shape mismatch.")
        return self.v_len < other.v_len

    def __le__(self, other) -> bool:
        """Implementation of operator "<=" between two vectors.

        Args:
            other (Vector): An object of class Vector.

        Returns:
            bool: Result of comparison in terms of "<=" operator.

        Raises:
            ValueError: If vectors differ in size.

        """
        if self.v_size != other.v_size:
            raise ValueError("vectors shape mismatch.")
        return self.v_len < other.v_len or abs(self.v_len - other.v_len) <= EPSILON

    def __gt__(self, other) -> bool:
        """Implementation of operator ">" between two vectors.

        Args:
            other (Vector): An object of class Vector.

        Returns:
            bool: Result of comparison in terms of ">" operator.

        Raises:
            ValueError: If vectors differ in size.

        """
        if self.v_size != other.v_size:
            raise ValueError("vectors shape mismatch.")
        return self.v_len > other.v_len

    def __ge__(self, other) -> bool:
        """Implementation of operator ">=" between two vectors.

        Args:
            other (Vector): An object of class Vector.

        Returns:
            bool: Result of comparison in terms of ">=" operator.

        Raises:
            ValueError: If vectors differ in size.

        """
        if self.v_size != other.v_size:
            raise ValueError("vectors shape mismatch.")
        return self.v_len > other.v_len or abs(self.v_len - other.v_len) <= EPSILON

    def check_input(self, v) -> bool:
        """Checks input. If input type is not tuple or list - raise TypeError.
        If input tuple/list has some elements that are not float/int - raise TypeError.

        Args:
            v: Input argument during class initialization.

        Returns:
            bool: Result of correct usage of implementation.

        Raises:
            TypeError: If wrong input is given.

        """
        if not isinstance(v, (list, tuple)):
            raise TypeError(
                "expected Any[Tuple[Any[float, int]], List[Tuple[Any[float, int]]].")

        for i in v:
            if not isinstance(i, (int, float)):
                raise TypeError(
                    "expected Any[Tuple[Any[float, int]], List[Tuple[Any[float, int]]].")

        self.v_len = sqrt(sum(list(map(lambda x: x**2, v))))
        self.v_size = len(v)

        return True
