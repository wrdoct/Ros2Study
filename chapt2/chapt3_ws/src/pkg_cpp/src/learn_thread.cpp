#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include "cpp-httplib/httplib.h"

class Download
{
private:
    /* data */
public:
    Download(/* args */) = default;
    ~Download() = default;

    void download(const std::string &host, const std::string &path, const std::function<void(const std::string &, const std::string &)> &callback_word_count)
    {
        std::cout << "线程" << std::this_thread::get_id() << std::endl;
        httplib::Client client(host);
        auto res = client.Get(path);
        if (res && res->status == 200)
        {
            callback_word_count(path, res->body);
        }
    };

    void start_download(const std::string &host, const std::string &path, const std::function<void(const std::string &, const std::string &)> &callback_word_count)
    {
        auto download_fun = std::bind(&Download::download, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        std::thread thread(download_fun, host, path, callback_word_count);
        thread.detach();
    };
};

int main()
{
    auto d = Download();
    auto word_count = [](const std::string &path, const std::string &res) -> void
    {
        std::cout << "下载完成" << path << ":" << res.length() << "->" << res.substr(0, 6) << std::endl;
    };
    d.start_download("http://0.0.0.0:8000", "/aaa.txt", word_count); // python3 -m http.server
    d.start_download("http://0.0.0.0:8000", "/bbb.txt", word_count);
    d.start_download("http://0.0.0.0:8000", "/ccc.txt", word_count);

    std::this_thread::sleep_for(std::chrono::microseconds(1000 * 10)); // 休眠10s
    return 0;
}