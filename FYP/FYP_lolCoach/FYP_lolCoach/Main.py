from RiotAPI import RiotAPI
import RiotConsts as Consts
import json 
import time


	
def pull_api():
	#try:		
	api=RiotAPI('xxx')
	activeplayername=api.get_active_player()
	#playername = json.dumps(activeplayerStats)
	activeplayerStats=api.get_active_player_stats()
	gamestats=api.get_gamestats()
	playerlist=api.get_playerlist()
	playerscore=api.get_playerscores(activeplayername)
	
	levelavg = 0
	playeramount = 0
	for i in playerlist:#cycle through all player levels and get average
		levelavg += playerlist[playeramount]["level"]
		playeramount+=1
		
	levelavg = levelavg/playeramount
	
	filedump = {
		"playername":activeplayername,
		"kills":playerscore["kills"],
		"deaths":playerscore["deaths"],
		"playerlevel":activeplayerStats["level"],
		"avglevel":round(levelavg),
		"time":gamestats["gameTime"],
		"isGameRunning":1  
	}
	results = open("results.json", "w")
	results.write(json.dumps(filedump))
	results.close()
	#print(json.dumps(filedump, indent=3))
	
	#except:
	#	print('There was a problem pulling from the game or creating a file\nGame must be ended')		
	#	filedump = {
	#		"playername":"",
	#		"kills":0,
	#		"deaths":0,
	#		"playerlevel":0,
	#		"avglevel":0,
	#		"time":0,
	#		"isGameRunning":0
	#	}
	#	results = open("results.json", "w")#create a json file
	#	results.write(json.dumps(filedump))
	#	results.close()
	#	print(json.dumps(filedump, indent=3))
	

def TimeLoop():
	timeTotal = 1 * 3600#max will be set to two mins
	pullmark = 0
	pull_api()#first pull before loop
	print('Entering time loop')
	while timeTotal>0 :
		time.sleep(1)#sleep for one second
		timeTotal-=1#decrtement 1 second
		pullmark+=1
		if pullmark==30 :#pull every 30 seconds
		#every 30secs, call request
			#make call
			#print('\nMinute passed\n')
			pull_api()
			pullmark=0
		
	#end loop

def main():
	print("Hello world Python")
	#r=api.get_summoner_by_name('Doubtless8')
	#r=api.get_active_player(Consts.URL['base'])	
	
	filedump = {
		"playername":"",
		"kills":0,
		"deaths":0,
		"playerlevel":0,
		"avglevel":0,
		"time":0,
		"isGameRunning":-1
	}
	results = open("results.json", "w")#create initial json file
	results.write(json.dumps(filedump))
	results.close()
	TimeLoop()
	

if __name__=="__main__":
	main()