#include <random>
#include <string>
#include <ctime>
#include "client.h"
#include "server.h"
#include "crypto.h"

using std::size_t;

    Client::Client(std::string id, const Server& server)
            : server(&server), id(std::move(id)) {
        crypto::generate_key(public_key, private_key);
    }

    std::string Client::get_id() {
        return id;
    }

    std::string Client::get_publickey() const {
        return public_key;
    }

    double Client::get_wallet() const {
        return server->get_wallet(id);
    }

    std::string Client::sign(std::string txt) const {
        return crypto::signMessage(private_key, txt);
    }

    bool Client::transfer_money(std::string receiver, double value) const {
        std::string trx = id;
        trx += "-";
        trx += receiver;
        trx += "-";
        trx += std::to_string(value);
        if (server->add_pending_trx(trx, crypto::signMessage(private_key, trx))) {
            return true;
        }
        return false;
    }

    size_t Client::generate_nonce() {
        std::mt19937 gen;
        gen.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist;
        return dist(gen);
    }
