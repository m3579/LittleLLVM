/*
 * Filename.hpp
 *
 * /Project/Headers/include/Filename.hpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Jan 12, 2016
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#ifndef CONSTRUCTTREEFORM_HPP
#define CONSTRUCTTREEFORM_HPP

namespace ast
{
    class ConstructTreeForm : ConstructTreeFormNode
    {
        public:
            ConstructTreeForm(std::string );
            virtual ~ConstructTreeForm();

            SP<ConstructTreeFormNode> subnode(std::string node);
            SP<ConstructTreeFormNode> subnode(std::vector<std::string> nodes);

            SP<ConstructTreeFormNode> get(std::string name);
            SP<ConstructTreeFormNode> get(std::vector<std::string> location);

        private:
            std::vector<SP<ConstructTreeFormNode>> tree;
    };
}

#endif // CONSTRUCTTREEFORM_HPP
