from typing import Protocol
from .vehicle import Vehicle

class RatePolicy(Protocol):
    def calculate(self, hours: float, v: Vehicle) -> float:
        ...

class HourlyRatePolicy:
    def __init__(self, car_rate: float, moto_rate: float):
        self._car_rate = car_rate
        self._moto_rate = moto_rate

    def calculate(self, hours: float, v: Vehicle) -> float:
        if v.get_type().name == "CAR":
            return hours * self._car_rate
        return hours * self._moto_rate