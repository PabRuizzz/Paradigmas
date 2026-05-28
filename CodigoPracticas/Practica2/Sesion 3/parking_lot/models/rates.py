from typing import Protocol
from .vehicle import Vehicle, VehicleType

class RatePolicy(Protocol):
    def calculate(self, hours: float, v: Vehicle) -> float:
        ...

class HourlyRatePolicy:
    def __init__(self, car_rate: float, moto_rate: float):
        self._car_rate = car_rate
        self._moto_rate = moto_rate

    def calculate(self, hours: float, v: Vehicle) -> float:
        # Polimorfismo por vehículo: costo distinto según el subtipo [cite: 250]
        if v.get_type() == VehicleType.CAR:
            return hours * self._car_rate
        elif v.get_type() == VehicleType.MOTORCYCLE:
            return hours * self._moto_rate
        return hours * 15.0 # Tarifa base por defecto