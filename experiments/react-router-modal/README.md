# React Router Modals

After browsing instagram I realized they are using react router to render modal on it, closing modal navigated away.

I realized I can use react router to render modal on that route, it seemed like better management for routes.

Pros:

- State is not required to render modal
- Modal rendering management is now route dependant
- Modal rendering may be grouped in routes
- Better overall management of modals

Cons:

- This example doesn't use portal, in larger app parent css might block modal css
