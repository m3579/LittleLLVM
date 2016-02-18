/*
 * Filename.hpp
 *
 * /Project/Headers/include/Filename.hpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Jan 16, 2016
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

// TODO: update include guards to match file names
#ifndef FLATNODELIST_HPP
#define FLATNODELIST_HPP

#include "FlatNodeListItem.hpp"
#include "FlatNode.hpp"
#include "ConstructTreeFormNode.hpp"

namespace parser
{
    class FlatNodeList : public FlatNodeListItem
    {
        public:
            FlatNodeList(std::string name);
            ~FlatNodeList();

            void addFlatNodeListItem(SP<FlatNodeListItem> flatNodeListItem);

            void populateFlatNodePool(std::vector<SP<FlatNode>>& flatNodePool);

            std::vector<SP<FlatNodeListItem>> getNodes();

            bool isLeaf();

            std::string getName();

            void print(std::string tabs);

            SP<ast::ConstructTreeFormNode> treeForm;

        private:
            std::vector<SP<FlatNodeListItem>> nodes;

            std::string name;
    };
}

#endif // FLATNODELIST_HPP
