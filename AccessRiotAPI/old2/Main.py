from RiotAPI import RiotAPI

def main():
	print("Hello world Python")
	api=RiotAPI('xxx')
	#r=api.get_summoner_by_name('Doubtless8')
	r=api.get_active_player()
	#r=api.get_champ_rotation(),
	print(r)

if __name__=="__main__":
	main()
