#include <Sea2.h>

using namespace sutils;
int main(int argc, char **argv)
{
    std::string str = "abc阿夜6哔";
    std::cout << "原字符串: " << str << std::endl;
    auto md5 = to_md5(str);
    std::cout << "默认小写 MD5: " << md5 << std::endl;
    md5 = to_md5(str, true);
    std::cout << "大写 MD5: " << md5 << std::endl;
    std::string b64_chars = "164pqrGF3bZwMfh/Ty29j7KHVnsxJDlX8EBegWC5+OzRuiNSmaPt0QLIkUYAdcov";
    std::string encoded = base64_encode(str, b64_chars);
    std::string decoded = base64_decode(encoded, b64_chars);

    std::cout << "自定义base64加密: " << encoded << std::endl;
    std::cout << "自定义base64解密: " << decoded << std::endl;

    auto hex = to_hex(str);
    std::cout << "默认小写 HEX: " << hex << std::endl;
    hex = to_hex(str, true);
    std::cout << "大写 HEX: " << hex << std::endl;

    std::cout << "当前时间戳: " << get_timestamp() << std::endl;

    auto sha = sha256(str);
    std::cout << "默认小写 sha256: " << sha << std::endl;
    sha = sha256(str, true);
    std::cout << "大写 sha256: " << sha << std::endl;

    std::string public_key = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAw0lDF9vj2o0KdiGeguV9fig+DCf+4WTf6hs5KDw7tFtqDFk9C6giFCP2K5SHNjH/PFYQ/Arn+ccBZwO/5wpz/HzKF41zgoF5gyEV1T1FoqjgC40HO7iXM1WO0ORTS4/T7U1obwHf42pfm4kjBkl/yzngPSdK7aBffI50kLc4gDlRQLffEP3ilKiEJ/HSOqtunadAXWUrnecn0CRdu+gZ1FlfLO7D1qcqaOl4dPtEgn/1tzr77fUMs7rElxaQvbV51R3HTuLz9HZfSg4ZNOqMzEx424T9XTvht0WKisTyhBd/xWUWevwYOMaarHDlJoqU/Hn04ALrrWpTeWAYW0rthQIDAQAB";
    std::string private_key = "MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQDDSUMX2+PajQp2IZ6C5X1+KD4MJ/7hZN/qGzkoPDu0W2oMWT0LqCIUI/YrlIc2Mf88VhD8Cuf5xwFnA7/nCnP8fMoXjXOCgXmDIRXVPUWiqOALjQc7uJczVY7Q5FNLj9PtTWhvAd/jal+biSMGSX/LOeA9J0rtoF98jnSQtziAOVFAt98Q/eKUqIQn8dI6q26dp0BdZSud5yfQJF276BnUWV8s7sPWpypo6Xh0+0SCf/W3Ovvt9QyzusSXFpC9tXnVHcdO4vP0dl9KDhk06ozMTHjbhP1dO+G3RYqKxPKEF3/FZRZ6/Bg4xpqscOUmipT8efTgAuutalN5YBhbSu2FAgMBAAECggEABItvbXOMwBjOg1pGm0A7pT8gK93rFL6+u+7Ulob0Ur8FNEgICiiTBnShys4tlAl3fvrNHA3QQTlW4y6sqB6k/V1qweqPo3Ffl7l3jcYGbqx5w6W4Dd/pW49PAAstlGbCpVVLAWOsnK5sjteTAkHyoJL2ZiXvHKGXUfQ/aotrsVwu9rf1zAL8MRz0yHGJI7HYb8J/Agl2Es74yc8t8ZZ3QjQByDWR26AGi9nNNk8jP9lbCdcK1UElQ9FOFlUBnn7Hu5RMJH1PHaIhwKHMqQPGSqL3y9U6z7d7f3eAOMohZbL4GFcV2SRilzfYjpBjYl+wLUks7lwJqRypfl2yNPd4HwKBgQD9WzgboPMxWhnvgmCO3YFXotl/nLzXA0r5MaCC01trZCgzhAWKXrLf5vs6UIetJtSCg2JgYAJcNzGRrblOw8dywh8LC0/PwlNqOB0c2ZYRIEUEBi3aHIiVMBtwMUWu1g+U/nzckbfH1odYAmhxk6e2bAggA/BdZLrO3yv8QsSYKwKBgQDFUuwi5LTbylL0iMFsHOh+f3HkzpD7EP438ZQYGdtYW8gZPm9MPDDpieatzOMBlOrGyYb5qzaqZOKfizZha4aJmf9s7zXFV426uch8GB3ogo3xorqmGefT/es9PeHt2laBdG8spAuY7w5s+kZXTY1B0v6CfsC5rRcJOj7BioWJDwKBgDxOqlxpQ3pL6ECK2FEpiNBDg2JM/OZxcjc/COYbSXeWr7sTgf4d7JY/dS28XY9p3svyWkh2khlBShtTLvkAwUkfzCPk3Wqm5xQxpzxmzsHk3IjIr8FraVeZy+44zE2BxtPAgBhA125KMo1QhWwDqbhSntyAE4cnow/7L40sl39hAoGARZ4V9dGfBZSCZAgDxfMFC+xG8KT4fbvnFTHEQCSPQMNQ+6cNeWYbE6o1msgYpyw1EOF1H40Kgl+JnSRukTxwgQe2GGblH7TeKiz10OJpWukEz2XMWGH3atHBNyAoH9TShGXh+2v9M33UJxq9yntwBPM+HChAMsIgyH6mOX530n0CgYEA014CtMmpWVZau+etxm7lKAubC414o6XwZuNxodQo88M0LJxQMCeiUPEzq03Igcaf5qAGothqjlx2+7fEDvTgLuT6FRgUcXtmu8Fs7PWKVi/0g0mct3ctPn28WrlZ1NORo5YtFeGB44/yYoje7WdNpR0zWLTblhpC8bW8i98gXcA=";

    auto pub_key = pem_format(public_key, false);
    auto pri_key = pem_format(private_key, true);

    // 公钥加密-私钥解密
    auto encrypt_text = rsa_public_encrypt(str, pub_key);
    encrypt_text = sutils::base64_encode(encrypt_text);
    std::cout << "公钥加密: " << encrypt_text << std::endl;
    auto decrypt_text = rsa_private_decrypt(sutils::base64_decode(encrypt_text), pri_key);
    std::cout << "私钥解密: " << decrypt_text << std::endl;

    // 私钥加密-公钥解密
    encrypt_text = rsa_private_encrypt(str, pri_key);
    encrypt_text = sutils::base64_encode(encrypt_text);
    std::cout << "私钥加密: " << encrypt_text << std::endl;
    decrypt_text = rsa_public_decrypt(sutils::base64_decode(encrypt_text), pub_key);
    std::cout << "公钥解密: " << decrypt_text << std::endl;

    /** 
	* get_imei(int,bool) int 1-3 log
	* 在Android设备su环境和普通环境的设备码会不一样
	* 如果没有特别需求你最好使用Java获取设备的imei
	* 这个imei为可执行文件设计(伪imei)
	*/
    auto imei = sutils::get_imei();
    std::cout << "IMEI(默认md5): " << imei << std::endl;
    imei = sutils::get_imei(2);
    std::cout << "IMEI(开启sha256): " << imei << std::endl;
    imei = sutils::get_imei(3);
    std::cout << "IMEI(base64): " << imei << std::endl;
	return 0;
}