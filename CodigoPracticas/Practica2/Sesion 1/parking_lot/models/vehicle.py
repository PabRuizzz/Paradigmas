from enum import Enum
from dataclasses import dataclass

class VehicleType(Enum):
    CAR = "CAR"
    MOTORCYCLE = "MOTORCYCLE"

@dataclass
class Vehicle:
    _plate: str
    _type: VehicleType

    def get_plate(self) -> str:
        return self._plate

    def get_type(self) -> VehicleType:
        return self._type