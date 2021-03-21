#ifndef    ACTION_HXX
# define   ACTION_HXX

# include "Action.hh"

namespace pge {

  inline
  Action::Action(const action::Process& cb,
                 const std::string& name):
    utils::CoreObject(name),

    m_callback(cb)
  {
    setService("action");
  }

  inline
  Action::~Action() {}

  inline
  void
  Action::apply(Game& g) const {
    m_callback(g);
  }

  inline
  void
  Action::setProcess(const action::Process& cb) {
    m_callback = cb;
  }

}

#endif    /* ACTION_HXX */
