#include "uagents.h"
#include <strings.h>
#include <string.h>
#include <stdlib.h>

const char* uagents[] = {

 //web browsers (2026)
 "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:145.0) Gecko/20100101 Firefox/145.0",
 "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/142.0.0.0 Safari/537.36",
 "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/19.0 Safari/605.1.15",
 "Mozilla/5.0 (Linux; Android 16; Pixel 9) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/142.0.0.0 Mobile Safari/537.36",
 "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/142.0.0.0 Safari/537.36 OPR/122.0.0.0",
 "Mozilla/5.0 (Linux; Android 16) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/142.0.0.0 Mobile Safari/537.36 OPR/92.0.0.0",
 "Mozilla/5.0 (Android 16; Mobile; rv:145.0) Gecko/145.0 Firefox/145.0",
 "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/142.0.0.0 Safari/537.36 Edg/142.0.0.0",

 //crawlers (2026)
 "Mozilla/5.0 AppleWebKit/537.36 (KHTML, like Gecko; compatible; Googlebot/2.1; +http://www.google.com/bot.html) Chrome/142.0.0.0 Safari/537.36",
 "Mozilla/5.0 AppleWebKit/537.36 (KHTML, like Gecko; compatible; bingbot/2.0; +http://www.bing.com/bingbot.htm) Chrome/142.0.0.0 Safari/537.36",
 "Mozilla/5.0 (compatible; Baiduspider/2.0; +http://www.baidu.com/search/spider.html)"
};


const char* resolve_ua(char* ua_short) {

	extern const char* uagents[];
	
    if (strcmp(ua_short,"ff") == 0) return uagents[0];
	if (strcmp(ua_short,"chr") == 0) return uagents[1];
	if (strcmp(ua_short,"saf") == 0) return uagents[2];
	if (strcmp(ua_short,"bb") == 0) return uagents[3];
	if (strcmp(ua_short,"ope") == 0) return uagents[4];
	if (strcmp(ua_short,"opem") == 0) return uagents[5];
	if (strcmp(ua_short,"fen") == 0) return uagents[6];
	if (strcmp(ua_short,"ie") == 0) return uagents[7];
	if (strcmp(ua_short,"gbot") == 0) return uagents[8];
	if (strcmp(ua_short,"bing") == 0) return uagents[9];
	if (strcmp(ua_short,"bspid") == 0) return uagents[10];
	return NULL;
    
}