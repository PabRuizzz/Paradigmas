from enum import Enum
from abc import ABC, abstractmethod

class VehicleType(Enum):
    CAR = "CAR"
    MOTORCYCLE = "MOTORCYCLE"

class Vehicle(ABC):
    def __init__(self, plate: str, v_type: VehicleType):
        self._plate = plate
        self._type = v_type

    def get_plate(self) -> str:
        return self._plate

    def get_type(self) -> VehicleType:
        return self._type

# Subtipos requeridos para la Sesión 2 [cite: 255]
class Car(Vehicle):
    def __init__(self, plate: str):
        super().__init__(plate, VehicleType.CAR)

class Motorcycle(Vehicle):
    def __init__(self, plate: str):
        super().__init__(plate, VehicleType.MOTORCYCLE)