#importing the needed classes and parameters from the other files
from Classes import Players
from Classes import Player_1
from Classes import Player_2
from Gadgets import weapons
from Gadgets import shields

# method for the game logic
def main():
  Gru=Player_1("GRU",health=100,energy=500,weapon=0,shield=0) 
  Villain=Player_2("Villain",health=100,energy=500,weapon=0,shield=0)
  
  # defining variables
  number_of_rounds = 1
  Gru_damage = 0
  Villain_damage = 0
  
  # game loop that ends when one villain's health reaches 0
  while Gru.health>0 and Villain.health>0 :
      
      print("choose Gru's action")
      Gru_action = Gru.choose_action() 
      if Gru_action ==0 :
          print("not a valid option")
          Gru.choose_action()
      elif Gru_action == 1 :    # the case of attack for player_1
         Gru_damage ,Gru.energy = Gru.attack()
         Villain.health -= Gru_damage
         if Gru_damage==0 :     # checking if the player can afford to attack or defense and if not he loses
             print("Gru doesn't have enough energy , Villain wins")
             break   
      elif Gru_action == 2 :  # the case of defense for player_1
         Gru.health ,Gru.energy = Gru.defend(Villain_damage)   
          
      
      print("choose Villain's action")
      Villain_action = Villain.choose_action()
      if Villain_action ==0 :
          print("not a valid option")
          Villain.choose_action()
      elif Villain_action == 1 :      # the case of attack for player_2
         Villain_damage ,Villain.energy= Villain.attack()
         Gru.health -= Villain_damage
         if Villain_damage==0 :     # checking if the player can afford to attack or defense and if not he loses
             print("Villain doesn't have enough energy , Villain wins")
             break 
      elif Villain_action == 2 :     # the case of defence for player_2
         Villain.health,Villain.energy=Villain.defend(Gru_damage) 
         
      number_of_rounds +=1     # number of rounds keeps increasing until one player's health = 0
      
      
      print("The end of round",number_of_rounds-1)
      print("Gru's health is ",Gru.health,"  Gru's energy is ",Gru.energy)
      print("Villain's health is ",Villain.health,"  Villain's energy is ",Villain.energy)
      print("Gonig to round ",number_of_rounds)
      
      # checking the health of each player 
      if Gru.health <= 0 :
         print("Villain is the winner") 
         break
      elif Villain.health <= 0 :
         print("Gru is the winner") 
         break        

# Entry point for the script
if __name__ == "__main__":
    main()         
