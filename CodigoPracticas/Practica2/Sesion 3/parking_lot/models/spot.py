from enum import Enum
from typing import Optional
from .vehicle import Vehicle, VehicleType

class SpotType(Enum):
    CAR = "CAR"
    MOTORCYCLE = "MOTORCYCLE"
    ANY = "ANY"

class ParkingSpot:
    def __init__(self, spot_id: str, allowed: SpotType):
        self._spot_id = spot_id
        self._allowed = allowed
        self._occupied = False
        self._current_vehicle: Optional[Vehicle] = None

    @property
    def spot_id(self) -> str:
        return self._spot_id

    @property
    def occupied(self) -> bool:
        return self._occupied

    def is_available_for(self, v: Vehicle) -> bool:
        if self._occupied:
            return False
        
        # Reglas de compatibilidad: spots que aceptan solo cierto tipo 
        if self._allowed == SpotType.ANY:
            return True
        return self._allowed.name == v.get_type().name

    def park(self, v: Vehicle) -> None:
        if not self.is_available_for(v):
            # Manejo de errores con mensajes claros [cite: 252]
            raise ValueError(f"Error: El spot {self._spot_id} no es compatible con un {v.get_type().name}")
        self._occupied = True
        self._current_vehicle = v

    def release(self) -> None:
        self._occupied = False
        self._current_vehicle = None