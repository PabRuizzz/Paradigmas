from enum import Enum
from datetime import datetime
from typing import Optional
from .vehicle import Vehicle
from .spot import ParkingSpot

class TicketStatus(Enum):
    ACTIVE = "ACTIVE"
    CLOSED = "CLOSED"

class Ticket:
    def __init__(self, ticket_id: int, vehicle: Vehicle, spot: ParkingSpot, entry_time: datetime):
        self._ticket_id = ticket_id
        self._vehicle = vehicle
        self._spot = spot
        self._entry_time = entry_time
        self._exit_time: Optional[datetime] = None
        self._status = TicketStatus.ACTIVE

    @property
    def ticket_id(self) -> int:
        return self._ticket_id

    @property
    def vehicle(self) -> Vehicle:
        return self._vehicle

    @property
    def spot(self) -> ParkingSpot:
        return self._spot

    @property
    def status(self) -> TicketStatus:
        return self._status

    def close(self, exit_time: datetime) -> None:
        if self._status == TicketStatus.CLOSED:
            raise ValueError("El ticket ya se encuentra cerrado.")
        self._exit_time = exit_time
        self._status = TicketStatus.CLOSED

    def get_duration_hours(self) -> float:
        if not self._exit_time:
            return 0.0
        delta = self._exit_time - self._entry_time
        # Retornamos el total de horas (minimo 1 hora cobrada)
        return max(1.0, delta.total_seconds() / 3600.0)