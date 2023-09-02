# the class for the weapons
class weapons:
    def __init__(self,name,energy,damage,resources):
        self.name = name
        self.energy = energy
        self.damage = damage
        self.resources = resources 
        
# the class for the shields        
class shields:
    def __init__(self,name,energy,save,resources):
        self.name = name
        self.energy = energy
        self.save = save
        self.resources = resources

# The weapons available for player_1 (Gru)
weapon_1={1: weapons(name="freeze_gun",energy=50,damage=11,resources=20),
          2: weapons(name="electric_prod",energy=88,damage=18,resources=5),
          3: weapons(name="mega_magnet",energy=92,damage=10,resources=3),
          4: weapons(name="kalman_missle",energy=120,damage=20,resources=1)}
# The weapons available for player_2 (Villain)
weapon_2={1: weapons(name="laser_blasters",energy=40,damage=8,resources=20),
          2: weapons(name="plasma_grenades",energy=56,damage=13,resources=8),
          3: weapons(name="sonic_resonance_cannon",energy=100,damage=22,resources=3)}
# The shields available for player_1 (Gru)
shield_1={1: shields(name="barrier_gun",energy=20,save=0.4,resources=20),
          2: shields(name="selective_permeability",energy=50,save=0.9,resources=2)}
# The shields available for player_2 (Villain)
shield_2={1: shields(name="energy_net",energy=15,save=0.32,resources=20),
          2: shields(name="quantum_deflector",energy=40,save=0.8,resources=3)}