#import <Foundation/Foundation.h>
#import "AFHTTPSessionManager.h"

/**
 * A key for `NSError` user info dictionaries.
 *
 * The corresponding value is the parsed response body for an HTTP error.
 */
extern NSString *const SWGResponseObjectErrorKey;

@class SWGApiClient;

typedef BOOL(^LogRequestsFilterBlock)(SWGApiClient *client, NSURLRequest *request, id responseData, NSError *error);

@interface SWGApiClient : AFHTTPSessionManager

/**
 * Get the Api Client instance from pool
 *
 * @param baseUrl The base url of api client.
 *
 * @return The SWGApiClient instance.
 */
+(SWGApiClient *)sharedClientFromPool:(NSString *)baseUrl;


/**
 * Set whether to log request/response
 *
 *
 */
+ (BOOL) logRequests;
+ (void) setLogRequests:(BOOL)logRequests;
+ (void) setLogRequestsFilterBlock:(LogRequestsFilterBlock)filterBlock;

/**
 * Get the request queue size
 *
 * @return The size of `queuedRequests` static variable.
 */
+(unsigned long)requestQueueSize;

/**
 * URL encode NSString
 *
 * @param unescaped The string which will be escaped.
 *
 * @return The escaped string.
 */
+(NSString*) escape:(id)unescaped;

/**
 * Detect Accept header from accepts NSArray
 *
 * @param accepts NSArray of header
 *
 * @return The Accept header
 */
+(NSString *) selectHeaderAccept:(NSArray *)accepts;

/**
 * Detect Content-Type header from contentTypes NSArray
 *
 * @param contentTypes NSArray of header
 *
 * @return The Content-Type header
 */
+(NSString *) selectHeaderContentType:(NSArray *)contentTypes;

/**
 * Update header parameters and query parameters for authentication
 *
 * @param headers The header parameter will be udpated, passed by pointer to pointer.
 * @param querys The query parameters will be updated, passed by pointer to pointer.
 * @param authSettings The authentication names NSArray.
 */
- (void) updateHeaderParams:(NSDictionary **)headers
                queryParams:(NSDictionary **)querys
           WithAuthSettings:(NSArray *)authSettings;

/**
 * Perform request
 *
 * Request with non-empty response
 *
 * @param path Request url.
 * @param method Request method.
 * @param queryParams Request query parameters.
 * @param body Request body.
 * @param headerParams Request header parameters.
 * @param keyPaths Request key path setting,for example:timeoutInterval
 * @param authSettings Request authentication names.
 * @param requestContentType Request content-type.
 * @param responseContentType Response content-type.
 * @param completionBlock The block will be executed when the request completed.
 *
 * @return The request id.
 */
-(NSNumber*)  executeWithPath: (NSString*) path
                       method: (NSString*) method
                  queryParams: (NSDictionary*) queryParams
                         body: (id) body
                 headerParams: (NSDictionary*) headerParams
                     keyPaths: (NSDictionary*) keyPaths
                 authSettings: (NSArray *) authSettings
           requestContentType: (NSString*) requestContentType
          responseContentType: (NSString*) responseContentType
              completionBlock: (void (^)(id, NSError *))completionBlock;

/**
 * Remove request id from the queue
 *
 * @param requestId The request which will be removed.
 */
- (void) cancelRequest:(NSNumber*)requestId;

@end
