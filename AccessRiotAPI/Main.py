from RiotAPI import RiotAPI
import RiotConsts as Consts
import json 

def main():
	print("Hello world Python")
	api=RiotAPI('xxx')
	#r=api.get_summoner_by_name('Doubtless8')
	#r=api.get_active_player(Consts.URL['base'])
	
	activeplayername=api.get_active_player()
	#playername = json.dumps(activeplayerStats)
	activeplayerStats=api.get_active_player_stats()
	gamestats=api.get_gamestats()
	playerlist=api.get_playerlist()
	playerscore=api.get_playerscores(activeplayername)
	
	#r=api.get_champ_rotation(),
	print(json.dumps(activeplayername, indent=3), "\n********playername ^*********")
	print(json.dumps(activeplayerStats, indent=3), "\n*******playerstats ^**********")
	print(json.dumps(gamestats, indent=3), "\n********gamestats ^*********")
	print(json.dumps(playerlist, indent=3), "\n*******playerlist ^**********")
	print(json.dumps(playerscore, indent=3), "\n******score ^***********")
	print(playerlist[0]["level"])
	
	levelavg = 0
	playeramount = 0
	for i in playerlist:
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
	}
	#possibly read how many files and then write to a new 
	results = open("results.json", "w")
	results.write(json.dumps(filedump))
	results.close()

if __name__=="__main__":
	main()
