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
        
	def get_games(self, matchID_input):
		self.call = 1
		api_url = Consts.URL['match_info'].format(matchId=matchID_input)
		return self._request(api_url)
        
	def testmethod(self):
		print('Testing print method')
