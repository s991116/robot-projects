#!/usr/bin/env python
# An experimental talking twitter client for the Raspberry Pi
# written in Python, by Martin O'Hanlon
# www.stuffaboutcode.com

#from oauth.oauth import OAuthRequest, OAuthSignatureMethod_HMAC_SHA1
from hashlib import md5
import json, time, random, math, urllib, urllib2, pycurl, subprocess, sys

# twitter oauth keys, get your from dev.twitter.com
CONSUMER_KEY = 'consumer key'
CONSUMER_SECRET = 'consumer secret'
ACCESS_TOKEN = 'access token'
ACCESS_TOKEN_SECRET = 'access token secret'

# function to download a file from a url, used for testing
def downloadFile(url, fileName):
    fp = open(fileName, "wb")
    curl = pycurl.Curl()
    curl.setopt(pycurl.URL, url)
    curl.setopt(pycurl.WRITEDATA, fp)
    curl.perform()
    curl.close()
    fp.close()

# returns the appropriate google speech url for a particular phrase
def getGoogleSpeechURL(phrase):
    googleTranslateURL = "http://translate.google.com/translate_tts?tl=en&"
    parameters = {'q': phrase}
    data = urllib.urlencode(parameters)
    googleTranslateURL = "%s%s" % (googleTranslateURL,data)
    return googleTranslateURL

# function to download an mp3 file for a particular phrase, used for testing
def downloadSpeechFromText(phrase, fileName):
    googleSpeechURL = getGoogleSpeechURL(phrase)
    print googleSpeechURL
    downloadFile(googleSpeechURL, fileName)

# output phrase to audio using mplayer
def speakSpeechFromText(phrase):
    googleSpeechURL = getGoogleSpeechURL(phrase)
    subprocess.call(["mplayer",googleSpeechURL], shell=False, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# class for managing tokens
class Token(object):
    def __init__(self,key,secret):
        self.key = key
        self.secret = secret

    def _generate_nonce(self):
        random_number = ''.join(str(random.randint(0, 9)) for i in range(40))
        m = md5(str(time.time()) + str(random_number))
        return m.hexdigest()

# talking twitter client
class TalkingTwitterStreamClient:
    def __init__(self, streamURL):
        self.streamURL = streamURL
        self.buffer = ""
        self.conn = pycurl.Curl()
        self.conn.setopt(pycurl.URL, self.streamURL)
        self.conn.setopt(pycurl.WRITEFUNCTION, self.on_receive)
        self.conn.perform()

    def on_receive(self, data):
        sys.stdout.write(".")
        self.buffer += data
        if data.endswith("\n") and self.buffer.strip():
            content = json.loads(self.buffer)
            self.buffer = ""
            #debug - output json from buffer
            #print content

            if "friends" in content:
                self.friends = content["friends"]
           
            if "text" in content:
                print u"{0[user][name]}: {0[text]}".format(content).encode('utf-8')
                speakSpeechFromText(u"A tweet from {0[user][name]}".format(content))
  #downloadSpeechFromText(u"A tweet from {0[user][name]}".format(content), "./tweet.mp3")
                speakSpeechFromText(u"{0[text]}".format(content))
  #downloadSpeechFromText(u"{0[text]}".format(content), "./tweet.mp3")

# get the url needed to open the twitter user stream, including signature after authentication
#def getTwitterUserStreamURL():
#    STREAM_URL = "https://userstream.twitter.com/2/user.json"
#
#    access_token = Token(ACCESS_TOKEN,ACCESS_TOKEN_SECRET)
#    consumer = Token(CONSUMER_KEY,CONSUMER_SECRET)
#   
#    parameters = {
#        'oauth_consumer_key': CONSUMER_KEY,
#        'oauth_token': access_token.key,
#        'oauth_signature_method': 'HMAC-SHA1',
#        'oauth_timestamp': str(int(time.time())),
#        'oauth_nonce': access_token._generate_nonce(),
#        'oauth_version': '1.0',
#    }
#
#    oauth_request = OAuthRequest.from_token_and_callback(access_token,
#                    http_url=STREAM_URL,
#                    parameters=parameters)
#    signature_method = OAuthSignatureMethod_HMAC_SHA1()
#    signature = signature_method.build_signature(oauth_request, consumer, access_token)
#
#    parameters['oauth_signature'] = signature
#    data = urllib.urlencode(parameters)
#    return "%s?%s" % (STREAM_URL,data)

# Run Talking Twitter Client
#client = TalkingTwitterStreamClient(getTwitterUserStreamURL())

#some useful debug commands, comment out running the client and uncomment the command
#get twitter stream url, including oauth signature
#print getTwitterUserStreamURL()
#download a speech file from google
#downloadSpeechFromText("hello, how are you today", "./downloadedFile.mp3")
#output phrase to audio
#speakSpeechFromText("hello, how are you today")
#start talking twitter client