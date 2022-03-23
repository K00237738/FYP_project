import requests
import RiotConsts as Consts

class RiotAPI(object):

	def __init__(self, api_key, region=Consts.REGIONS['EUROPE']):
		self.api_key = api_key
		self.region = region
		self.call = 0
		print("Instantiated")

	def _request(self, api_url, params={}):
		if self.call == 2:
			query = ''
		args = {'api_key':self.api_key}
		for key, value in params.items():
			if key not in args:
				args[key]=value
		if self.call == 1:
			response=requests.get(
			Consts.URL['base'].format(
			region=self.region,
			query=api_url),params=args)
		print(response.url)
		return response.json()

	def get_summoner_by_name(self, name):
		print("Getting summoner by name")
		self.call = 1
		api_url = Consts.URL['summoner_by_name'].format(
			version=Consts.API_VERSIONS['summoner'],
			names=name
			)
		print("Returning")
		return self._request(api_url)

	def get_champ_rotation(self):
		self.call = 1
		api_url = Consts.URL['champ_rotation'].format()
		return self._request(api_url)

	def get_active_player(self):
		response=requests.get(Consts.URL['playername'].format(), verify=False)
		#if self.call == 2:
		#	query = ''
		#args = {'api_key':self.api_key}
		#for key, value in params.items():
		#	if key not in args:
		#		args[key]=value
		#if self.call == 1:
		#	response2=requests.get(
		#	Consts.URL['base2'].format(
		#	region=self.region,
		#	query=api_url),params=args)
		print(response.url)
		return response.json()

	def get_active_player_stats(self):
		response=requests.get(Consts.URL['activeplayerstats'].format(), verify=False)
		print(response.url)
		return response.json()

	def get_gamestats(self):
		response=requests.get(Consts.URL['gamestats'].format(), verify=False)
		print(response.url)
		return response.json()

	def get_playerlist(self):
		response=requests.get(Consts.URL['playerlist'].format(), verify=False)
		print(response.url)
		return response.json()

	def get_playerscores(self, playername):
		response=requests.get(Consts.URL['playerscores'].format(names=playername), verify=False)
		print(playername)
		print(response.url)
		return response.json()
		
	def get_games(self, matchID_input):
		self.call = 1
		api_url = Consts.URL['match_info'].format(matchId=matchID_input)
		return self._request(api_url)
		
	def testmethod(self):
		print('Testing print method')
