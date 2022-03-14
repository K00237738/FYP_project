from RiotAPI import RiotAPI
import RiotConsts as Consts
import json 

def main():
	print("Hello world Python")
	api=RiotAPI('xxx')
	#r=api.get_summoner_by_name('Doubtless8')
	r=api.get_active_player(Consts.URL['base'])
	#r=api.get_champ_rotation(),
	print(r)
	#possibly read how many files and then write to a new 
	#results = open("results.json", "w")
	#results.write(r)
	#results.close()

if __name__=="__main__":
	main()
