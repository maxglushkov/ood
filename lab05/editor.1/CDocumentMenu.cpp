#include "CDocumentMenu.hpp"

CDocumentMenu::CDocumentMenu(IDocument & document)
	:CMenu({
		{
			"InsertParagraph",
			"Inserts paragraph. Args: <position>|end <paragraph text>",
			[&](CArguments & args, std::ostream &)
			{
				const auto pos = args.PopPosition();
				document.InsertParagraph(args.PopLine(), pos);
			}
		}, {
			"InsertImage",
			"Inserts image. Args: <position>|end <width> <height> <path/to/image/file>",
			[&](CArguments & args, std::ostream &)
			{
				const auto pos = args.PopPosition();
				const auto width = args.Pop<int>();
				const auto height = args.Pop<int>();
				document.InsertImage(args.PopLine(), width, height, pos);
			}
		}, {
			"SetTitle",
			"Changes title. Args: <new title>",
			[&](CArguments & args, std::ostream &)
			{
				document.SetTitle(args.PopLine());
			}
		}, {
			"List",
			"Show document",
			[&](CArguments &, std::ostream & output)
			{
				output << "Title: " << document.GetTitle() << '\n';
				for (size_t index = 0; index < document.GetItemsCount(); ++index)
				{
					output << index << ". ";
					const auto item = document.GetItem(index);
					if (const auto image = item.GetImage())
					{
						output << "Image: " << image->GetWidth() << 'x' << image->GetHeight() << " @ " << image->GetPath();
					}
					else if (const auto paragraph = item.GetParagraph())
					{
						output << "Paragraph: " << paragraph->GetText();
					}
					output << '\n';
				}
			}
		}, {
			"ReplaceText",
			"Changes paragraph text. Args: <position> <new paragraph text>",
			[&](CArguments & args, std::ostream &)
			{
				const auto paragraph = document.GetItem(args.Pop<size_t>()).GetParagraph();
				if (!paragraph)
				{
					throw std::invalid_argument("requested item is not a paragraph");
				}
				paragraph->SetText(args.PopLine());
			}
		}, {
			"ResizeImage",
			"Changes image size. Args: <position> <width> <height>",
			[&](CArguments & args, std::ostream &)
			{
				const auto image = document.GetItem(args.Pop<size_t>()).GetImage();
				if (!image)
				{
					throw std::invalid_argument("requested item is not an image");
				}
				const auto width = args.Pop<int>();
				const auto height = args.Pop<int>();
				image->Resize(width, height);
			}
		}, {
			"DeleteItem",
			"Removes item. Args: <position>",
			[&](CArguments & args, std::ostream &)
			{
				document.DeleteItem(args.Pop<size_t>());
			}
		}, {
			"Help",
			"Help",
			[this](CArguments &, std::ostream & output)
			{
				for (auto & item: GetItems())
				{
					output << item.name << ": " << item.description << '\n';
				}
			}
		}, {
			"Undo",
			"Undo command",
			std::bind(&IDocument::Undo, &document)
		}, {
			"Redo",
			"Redo undone command",
			std::bind(&IDocument::Redo, &document)
		}, {
			"Save",
			"Saves document. Args: <path>",
			[&](CArguments & args, std::ostream &)
			{
				document.Save(args.PopLine());
			}
		}
	})
{}
