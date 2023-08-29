#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <map>
#include "client.h"
#include "server.h"

std::vector<std::string> pending_trxs;

    void  show_wallets(const  Server& server) {
        std::cout << std::string(20, '*') << std::endl;
        for(const auto& client: server.clients)
            std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
        std::cout << std::string(20, '*') << std::endl;
    }

    Server::Server() = default;

    std::shared_ptr<Client> Server::add_client(std::string id) {
        for (auto [client, wallet] : clients) {
            if (client->get_id() == id) {
                std::default_random_engine e;
                e.seed(time(0));
                std::size_t random_digit = e() % 10000;
                int cnt = 0;
                while (random_digit > 0 || cnt++ < 4) {
                    if (random_digit == 0) {
                        id += "0";
                    } else {
                        id += std::to_string(random_digit % 10);
                        random_digit >>= 1;
                    }
                }
            }
        }
        std::shared_ptr<Client> ptr = std::make_shared<Client>(id, *this);
        clients[ptr] = 5;

        return ptr;
    }

    std::shared_ptr<Client> Server::get_client(std::string id) const {
        for (auto [client_ptr, wallet] : clients) {
            if (client_ptr->get_id() == id) {
                return client_ptr;
            }
        }
        return nullptr;
    }

    double Server::get_wallet(std::string id) const {
        for (auto [client_ptr, wallet] : clients) {
            if (client_ptr->get_id() == id) {
                return wallet;
            }
        }
        return 0;
    }

    bool Server::parse_trx(const std::string& trx, std::string& sender, std::string& receiver, double& value) {
        std::istringstream iss(trx);
        std::string line;
        std::vector<std::string> vec;
        while (getline(iss, line, '-')) {
            vec.push_back(line);
        }
        if (vec.size() == 3) {
            sender = vec[0];
            receiver = vec[1];
            std::istringstream iss1(vec[2]);
            char remain;
            if (iss1 >> value && !(iss1 >> remain))
                return true;
        }
        throw std::runtime_error("input trx is invalid");
    }

    bool Server::add_pending_trx(std::string trx, std::string signature) const {
        std::string sender, receiver;
        double value;
        if (!parse_trx(trx, sender, receiver, value)) {
            return false;
        }
        std::shared_ptr<Client> sender_ptr = get_client(sender);
        std::shared_ptr<Client> receiver_ptr = get_client(receiver);
        if (!(sender_ptr && receiver_ptr)) {
            return false;
        }
        if (crypto::verifySignature
                (sender_ptr->get_publickey(), trx, std::move(signature))
                            && sender_ptr->get_wallet() > value) {
            pending_trxs.push_back(trx);
            return true;
        }

        return false;
    }

    size_t Server::mine() {
        std::string mempool;
        size_t nonce;
        for (std::string& trx : pending_trxs) {
            mempool.append(trx);
        }
        while (true) {
            bool mined = false;
            for (auto [client, wallet]: clients) {
                size_t gen_nonce = client->generate_nonce();
                std::string client_attempt = mempool + std::to_string(gen_nonce);
                std::string sha256 = crypto::sha256(client_attempt);
                if (sha256.substr(0, 10).find("000", 0) != std::string::npos) {
                    nonce = gen_nonce;
                    clients[client] += 6.25;
                    mined = true;
                    break;
                }
            }
            if (mined) {
                break;
            }
        }
        for (std::string trx : pending_trxs) {
            std::string sender, receiver;
            double value;
            parse_trx(trx, sender, receiver, value);
            std::shared_ptr<Client> sender_ptr, receiver_ptr;
            for (auto& [client, value] : clients) {
                if (client->get_id() == sender) {
                    sender_ptr = client;
                } else if (client->get_id() == receiver) {
                    receiver_ptr = client;
                }
            }
            clients[sender_ptr] -= value;
            clients[receiver_ptr] += value;
        }

        return nonce;
    }
