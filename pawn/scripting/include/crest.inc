#if defined _crest_included_
	#endinput
#endif
#define _crest_included_

enum HTTPStatus
{
	HTTPStatus_Invalid = 0,

	// 1xx Informational
	HTTPStatus_Continue = 100,
	HTTPStatus_SwitchingProtocols = 101,

	// 2xx Success
	HTTPStatus_OK = 200,
	HTTPStatus_Created = 201,
	HTTPStatus_Accepted = 202,
	HTTPStatus_NonAuthoritativeInformation = 203,
	HTTPStatus_NoContent = 204,
	HTTPStatus_ResetContent = 205,
	HTTPStatus_PartialContent = 206,

	// 3xx Redirection
	HTTPStatus_MultipleChoices = 300,
	HTTPStatus_MovedPermanently = 301,
	HTTPStatus_Found = 302,
	HTTPStatus_SeeOther = 303,
	HTTPStatus_NotModified = 304,
	HTTPStatus_UseProxy = 305,
	HTTPStatus_TemporaryRedirect = 307,
	HTTPStatus_PermanentRedirect = 308,

	// 4xx Client Error
	HTTPStatus_BadRequest = 400,
	HTTPStatus_Unauthorized = 401,
	HTTPStatus_PaymentRequired = 402,
	HTTPStatus_Forbidden = 403,
	HTTPStatus_NotFound = 404,
	HTTPStatus_MethodNotAllowed = 405,
	HTTPStatus_NotAcceptable = 406,
	HTTPStatus_ProxyAuthenticationRequired = 407,
	HTTPStatus_RequestTimeout = 408,
	HTTPStatus_Conflict = 409,
	HTTPStatus_Gone = 410,
	HTTPStatus_LengthRequired = 411,
	HTTPStatus_PreconditionFailed = 412,
	HTTPStatus_RequestEntityTooLarge = 413,
	HTTPStatus_RequestURITooLong = 414,
	HTTPStatus_UnsupportedMediaType = 415,
	HTTPStatus_RequestedRangeNotSatisfiable = 416,
	HTTPStatus_ExpectationFailed = 417,
	HTTPStatus_MisdirectedRequest = 421,
	HTTPStatus_TooEarly = 425,
	HTTPStatus_UpgradeRequired = 426,
	HTTPStatus_PreconditionRequired = 428,
	HTTPStatus_TooManyRequests = 429,
	HTTPStatus_RequestHeaderFieldsTooLarge = 431,
	HTTPStatus_UnavailableForLegalReasons = 451,

	// 5xx Server Error
	HTTPStatus_InternalServerError = 500,
	HTTPStatus_NotImplemented = 501,
	HTTPStatus_BadGateway = 502,
	HTTPStatus_ServiceUnavailable = 503,
	HTTPStatus_GatewayTimeout = 504,
	HTTPStatus_HTTPVersionNotSupported = 505,
	HTTPStatus_VariantAlsoNegotiates = 506,
	HTTPStatus_NotExtended = 510,
	HTTPStatus_NetworkAuthenticationRequired = 511,
};

typeset HTTPRequestCallback
{
	function void (HTTPRes response, any value);
	function void (HTTPRes response, any value, const char[] error);
};

typeset HTTPFileCallback
{
	function void (HTTPStatus status, any value);
	function void (HTTPStatus status, any value, const char[] error);
};

methodmap HTTPReq < Handle
{
	// Creates an HTTP request.
	//
	// The Handle is automatically freed when the request is performed.
	// Otherwise, the Handle must be freed via delete or CloseHandle().
	//
	// @param url        URL to the REST API endpoint.
	public native HTTPReq(const char[] url);

	// Appends a parameter to the form data.
	//
	// The parameter name and value are encoded according to RFC 3986.
	//
	// @param name       Parameter name.
    // @param format     Formatting rules.
    // @param ...        Variable number of format parameters.
	public native void AppendFormParam(const char[] name, const char[] format, any ...);

	// Appends a query parameter to the URL.
	//
	// The parameter name and value are encoded according to RFC 3986.
	//
	// @param name       Parameter name.
    // @param format     Formatting rules.
    // @param ...        Variable number of format parameters.
	public native void AppendQueryParam(const char[] name, const char[] format, any ...);

	// Sets the credentials for HTTP Basic authentication.
	//
	// @param username   Username to use.
	// @param password   Password to use.
	public native void SetBasicAuth(const char[] username, const char[] password);

	// Sets an HTTP header.
	//
	// @param name       Header name.
    // @param format     Formatting rules.
    // @param ...        Variable number of format parameters.
	public native void SetHeader(const char[] name, const char[] format, any ...);

	// Performs an HTTP GET request.
	//
	// This function closes the request Handle after completing.
	//
	// @param callback   A function to use as a callback when the request has finished.
	// @param value      Optional value to pass to the callback function.
	public native void Get(HTTPRequestCallback callback, any value = 0);

	// Performs an HTTP POST request.
	//
	// This function closes the request Handle after completing.
	//
	// @param data       JSON data to send.
	// @param callback   A function to use as a callback when the request has finished.
	// @param value      Optional value to pass to the callback function.
	public native void Post(const char[] data, HTTPRequestCallback callback, any value = 0);

	// Performs an HTTP PUT request.
	//
	// This function closes the request Handle after completing.
	//
	// @param data       JSON data to send.
	// @param callback   A function to use as a callback when the request has finished.
	// @param value      Optional value to pass to the callback function.
	public native void Put(const char[] data, HTTPRequestCallback callback, any value = 0);

	// Performs an HTTP PATCH request.
	//
	// This function closes the request Handle after completing.
	//
	// @param data       JSON data to send.
	// @param callback   A function to use as a callback when the request has finished.
	// @param value      Optional value to pass to the callback function.
	public native void Patch(const char[] data, HTTPRequestCallback callback, any value = 0);

	// Performs an HTTP DELETE request.
	//
	// This function closes the request Handle after completing.
	//
	// @param callback   A function to use as a callback when the request has finished.
	// @param value      Optional value to pass to the callback function.
	public native void Delete(HTTPRequestCallback callback, any value = 0);

	// Downloads a file.
	//
	// This function closes the request Handle after completing.
	//
	// @param path       File path to write to.
	// @param callback   A function to use as a callback when the download has finished.
	// @param value      Optional value to pass to the callback function.
	public native void DownloadFile(const char[] path, HTTPFileCallback callback, any value = 0);

	// Uploads a file.
	//
	// This function performs an HTTP PUT request. The file contents are sent in the request body.
	// This function closes the request Handle after completing.
	//
	// @param path       File path to read from.
	// @param callback   A function to use as a callback when the upload has finished.
	// @param value      Optional value to pass to the callback function.
	public native void UploadFile(const char[] path, HTTPFileCallback callback, any value = 0);

	// Performs an HTTP POST request with form data.
	//
	// This function closes the request Handle after completing.
	//
	// @param callback   A function to use as a callback when the request has finished.
	// @param value      Optional value to pass to the callback function.
	public native void PostForm(HTTPRequestCallback callback, any value = 0);

	// Connect timeout in seconds. Defaults to 10.
	property int ConnectTimeout {
		public native get();
		public native set(int connectTimeout);
	}

	// Maximum number of redirects to follow. Defaults to 5.
	property int MaxRedirects {
		public native get();
		public native set(int maxRedirects);
	}

	// Maximum download speed in bytes per second. Defaults to unlimited speed.
	property int MaxRecvSpeed {
		public native get();
		public native set(int maxSpeed);
	}

	// Maximum upload speed in bytes per second. Defaults to unlimited speed.
	property int MaxSendSpeed {
		public native get();
		public native set(int maxSpeed);
	}

	// Timeout in seconds. Defaults to 30.
	property int Timeout {
		public native get();
		public native set(int timeout);
	}
}

methodmap HTTPRes < Handle
{
	// Retrieves an HTTP header from the response.
	//
	// @param name       Header name.
	// @param buffer     String buffer to store value.
	// @param maxlength  Maximum length of the string buffer.
	// @return           True on success, false if the header was not found.
	public native bool GetHeader(const char[] name, char[] buffer, int maxlength);

	// Retrieves an json body from the response.
	//
	// @param buffer     String buffer to store value.
	// @param maxlength  Maximum length of the string buffer.
	// @return           error code (0 on success).
	public native int GetData(char[] buffer, int maxlength);

	// Retrieves the data length of the response.
	property int DataLength {
		public native get();
	}

	// Retrieves the HTTP status of the response.
	property HTTPStatus Status {
		public native get();
	}
};

// Deprecated. Use HTTPReq instead.
methodmap HTTP < Handle
{
	// Creates an HTTP client.
	//
	// The HTTP must be freed via delete or CloseHandle().
	//
	// @param baseURL    Base URL to the REST API.
	#pragma deprecated Use HTTPReq instead.
	public native HTTP(const char[] baseURL);

	// Sets an HTTP header to be used for all requests.
	//
	// @param name       Header name.
	// @param value      String value to set.
	#pragma deprecated Use HTTPReq.SetHeader() instead.
	public native void SetHeader(const char[] name, const char[] value);

	// Performs an HTTP GET request.
	//
	// @param endpoint   API endpoint to request.
	// @param callback   A function to use as a callback when the request has finished.
	// @param value      Optional value to pass to the callback function.
	#pragma deprecated Use HTTPReq.Get() instead.
	public native void Get(const char[] endpoint, HTTPRequestCallback callback, any value = 0);

	// Performs an HTTP POST request.
	//
	// @param endpoint   API endpoint to request.
	// @param data       JSON data to send.
	// @param callback   A function to use as a callback when the request has finished.
	// @param value      Optional value to pass to the callback function.
	#pragma deprecated Use HTTPReq.Post() instead.
	public native void Post(const char[] endpoint, const char[] data, HTTPRequestCallback callback, any value = 0);

	// Performs an HTTP PUT request.
	//
	// @param endpoint   API endpoint to request.
	// @param data       JSON data to send.
	// @param callback   A function to use as a callback when the request has finished.
	// @param value      Optional value to pass to the callback function.
	#pragma deprecated Use HTTPReq.Put() instead.
	public native void Put(const char[] endpoint, const char[] data, HTTPRequestCallback callback, any value = 0);

	// Performs an HTTP PATCH request.
	//
	// @param endpoint   API endpoint to request.
	// @param data       JSON data to send.
	// @param callback   A function to use as a callback when the request has finished.
	// @param value      Optional value to pass to the callback function.
	#pragma deprecated Use HTTPReq.Patch() instead.
	public native void Patch(const char[] endpoint, const char[] data, HTTPRequestCallback callback, any value = 0);

	// Performs an HTTP DELETE request.
	//
	// @param endpoint   API endpoint to request.
	// @param callback   A function to use as a callback when the request has finished.
	// @param value      Optional value to pass to the callback function.
	#pragma deprecated Use HTTPReq.Delete() instead.
	public native void Delete(const char[] endpoint, HTTPRequestCallback callback, any value = 0);

	// Downloads a file.
	//
	// @param endpoint   API endpoint to download from.
	// @param path       File path to write to.
	// @param callback   A function to use as a callback when the download has finished.
	// @param value      Optional value to pass to the callback function.
	#pragma deprecated Use HTTPReq.DownloadFile() instead.
	public native void DownloadFile(const char[] endpoint, const char[] path, HTTPFileCallback callback, any value = 0);

	// Uploads a file.
	//
	// This function performs an HTTP PUT request. The file contents are sent in the request body.
	//
	// @param endpoint   API endpoint to upload to.
	// @param path       File path to read from.
	// @param callback   A function to use as a callback when the upload has finished.
	// @param value      Optional value to pass to the callback function.
	#pragma deprecated Use HTTPReq.UploadFile() instead.
	public native void UploadFile(const char[] endpoint, const char[] path, HTTPFileCallback callback, any value = 0);

	// Connect timeout in seconds. Defaults to 10.
	#pragma deprecated Use HTTPReq.ConnectTimeout instead.
	property int ConnectTimeout {
		public native get();
		public native set(int connectTimeout);
	}

	// Follow HTTP 3xx redirects. Defaults to true.
	#pragma deprecated Use HTTPReq.MaxRedirects instead.
	property bool FollowLocation {
		public native get();
		public native set(bool followLocation);
	}

	// Timeout in seconds. Defaults to 30.
	#pragma deprecated Use HTTPReq.Timeout instead.
	property int Timeout {
		public native get();
		public native set(int timeout);
	}

	// Maximum upload speed in bytes per second. Defaults to unlimited speed.
	#pragma deprecated Use HTTPReq.MaxSendSpeed instead.
	property int MaxSendSpeed {
		public native get();
		public native set(int speed);
	}

	// Maximum download speed in bytes per second. Defaults to unlimited speed.
	#pragma deprecated Use HTTPReq.MaxRecvSpeed instead.
	property int MaxRecvSpeed {
		public native get();
		public native set(int speed);
	}
};


/**
 * Do not edit below this line!
 */
public Extension __ext_crest =
{
	name = "C REST",
	file = "crest.ext",
#if defined AUTOLOAD_EXTENSIONS
	autoload = 1,
#else
	autoload = 0,
#endif
#if defined REQUIRE_EXTENSIONS
	required = 1,
#else
	required = 0,
#endif
};
