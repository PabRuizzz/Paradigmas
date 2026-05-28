from datetime import datetime
from typing import List, Dict
from .vehicle import Vehicle
from .spot import ParkingSpot
from .ticket import Ticket
from .rates import RatePolicy

class ParkingLot:
    def __init__(self, spots: List[ParkingSpot], policy: RatePolicy):
        self._spots = spots
        self._active_tickets: Dict[int, Ticket] = {}
        self._policy = policy
        self._next_ticket_id = 1
        self._total_revenue = 0.0

    def enter(self, v: Vehicle, now: datetime) -> Ticket:
        # Busca el primer spot disponible y compatible
        available_spot = next((s for s in self._spots if s.is_available_for(v)), None)
        if not available_spot:
            raise ValueError("Estacionamiento lleno o sin lugares compatibles.")

        available_spot.park(v)
        ticket = Ticket(self._next_ticket_id, v, available_spot, now)
        self._active_tickets[self._next_ticket_id] = ticket
        self._next_ticket_id += 1
        return ticket

    def exit(self, ticket_id: int, now: datetime) -> float:
        if ticket_id not in self._active_tickets:
            raise ValueError("Ticket no encontrado o inválido.")

        ticket = self._active_tickets.pop(ticket_id)
        ticket.close(now)
        
        hours = ticket.get_duration_hours()
        cost = self._policy.calculate(hours, ticket.vehicle)
        
        ticket.spot.release()
        self._total_revenue += cost
        return cost

    def get_occupancy(self) -> str:
        libres = sum(1 for s in self._spots if not s.occupied)
        ocupados = len(self._spots) - libres
        return f"libres={libres} ocupados={ocupados}"

    def get_active_tickets(self) -> List[Ticket]:
        return list(self._active_tickets.values())