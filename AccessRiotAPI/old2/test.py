#from Main import main
#main()
from RiotAPI import RiotAPI

print('Printed stuff')
api = RiotAPI('RGAPI-c588ebd2-8205-47e3-993d-629654316a08')
#api.testmethod()
#r = api.get_summoner_by_name('Doubtless8')
#print(r)
#r = api.get_champ_rotation()
#print(r)
r = api.get_games('EUW1_5506259385')
print(r)