#import the needed parameters from other files
from Gadgets import weapon_1
from Gadgets import weapon_2
from Gadgets import shield_1
from Gadgets import shield_2

#The superclass of players 
class Players:
    #constructor
    def __init__(self, name,health,energy):
        #Instance attributes
        self.name = name
        self.health = health
        self.energy = energy
        
    #Method for players to choose the action in this round     
    def choose_action(self):
        choice = int (input ('''1- attack using selected weapon
2- defend using selected shield
your choice is '''))
        if choice==1 or choice==2:
            return choice
        else:
            return self.choose_action()

# class for player1 (Gru) which is a subclass from the class players
class Player_1(Players):
    def __init__(self,name,health,energy,weapon,shield):
        super().__init__(name,health,energy)   #inheratance from class players
        #Instance attributes
        self.weapon=weapon_1
        self.shield=shield_1
    
    #method for attacking 
    def attack(self): 
      weapon_1 = int(input ('''choose GRU's weapon:
1- Freeze Gun
2- Electric Prod
3- Mega Magnet
4- Kalman Missle
your choice is '''))  
      selected_weapon = self.weapon.get(weapon_1)       # gettin the choosen weapon from dictt weapon_1
      if selected_weapon:
          if self.energy >= selected_weapon.energy:     # checking if player has enough energy
              self.energy -= selected_weapon.energy     
              damage = selected_weapon.damage
              selected_weapon.resources -=1
              return damage, self.energy
          else :
             return 0,self.energy       
      else:                         
          print("not a valid choice")
          return self.attack()
          
    # method for defending       
    def defend (self,damage):               #taking the damage caused by the other player as a parameter
      shield_1=int (input('''choose GRU's shield: 
 1- Energy Projected BarrierGun
 2- Selective Permeability
 your choice is '''))        
      selected_shield = self.shield.get(shield_1)        # gettin the choosen shield from dictt shield_1
      if selected_shield :
          if self.energy >= selected_shield.energy:       # checking if player has enough energy
             self.energy -= selected_shield.energy
             real_damage = damage - (damage * selected_shield.save)
             self.health -= real_damage
             selected_shield.resources -=1
             return self.health, self.energy
          else :
              return self.health ,self.energy
      else:
          print("not a valid choice")
          return 0
      
# class for player2 (Villain) which is a subclass from the class players      
class Player_2(Players):
    def __init__(self,name,health,energy,weapon,shield):
        super().__init__(name,health,energy)                #inheratance from class players
        #Instance attributes
        self.weapon=weapon_2
        self.shield=shield_2
    
    def attack(self): 
      weapon_2 = int(input ('''choose Villain's weapon:
1- Laser blasters
2- Plasma Grenades
3- Sonic Resonance Cannon
your choice is '''))  
      selected_weapon = self.weapon.get(weapon_2)     # gettin the choosen weapon from dictt weapon_2 
      if selected_weapon:
         if self.energy >= selected_weapon.energy:    # checking if player has enough energy
               self.energy -= selected_weapon.energy   
               damage = selected_weapon.damage
               selected_weapon.resources -=1
               return damage, self.energy
         else :
             return 0,self.energey
      else:
          print("not a valid choice")
          return self.attack()         
 
    # method for defending      
    def defend (self,damage):        #taking the damage caused by the other player as a parameter
      shield_2=int (input('''choose VILLAIN's shield: 
1- Energy Net Trap
2- Quantum Deflector
your choice is ''')) 
      selected_shield= self.shield.get(shield_2)       # gettin the choosen shield from dictt shield_2
      if selected_shield :
          if self.energy >= selected_shield.energy:   # checking if player has enough energy
             self.energy -= selected_shield.energy
             real_damage = damage - (damage * selected_shield.save)
             self.health -= real_damage
             selected_shield.resources -=1
             return self.health,self.energy
          else :
              return self.health ,self.energy
      else:
          print("not a valid choice")
          return 0              
