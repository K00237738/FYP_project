URL = {
        #'base': 'https://{proxy}.api.pvp.net/api/lol/{region}/{url}',
        #'base': 'https://{region}.api.riotgames.com/lol/summoner/',
        #'base': 'https://{proxy}.api.riotgames.com/api/lol/{region}/{url}',
        #'summoner_by_name': 'v{version}/summoners/by-name/{names}',
        
        #'base': 'https://{region}.api.riotgames.com/lol/summoner/v{version}/summoners/by-name/{names}/',
        'base': 'https://{region}.api.riotgames.com/{query}',
        'summoner_by_name': 'lol/summoner/v{version}/summoners/by-name/{names}',
        'champ_rotation': 'lol/platform/v3/champion-rotations',
        'match_info': 'lol/match/v5/matches/{matchId}'
        
        #'summoner_by_name': 'v{version}/summoner/by-name/{names}'
    }

API_VERSIONS = {
        'summoner': '4'
    }

REGIONS = {
        #'europe_nordic_and_east': 'eune',
        #'europe_west': 'euw'
        
        'EUROPE': 'euw1'#uncomment this for other queries
        #'EUROPE': 'europe'#uncomment this out for match details
    }
