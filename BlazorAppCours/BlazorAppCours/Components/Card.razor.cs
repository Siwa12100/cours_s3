using Microsoft.AspNetCore.Components;

namespace BlazorAppCours.Components
{
    public partial class Card<TItem>
    {
        [Parameter]
        public RenderFragment<TItem> CardBody { get; set; }

        [Parameter]
        public RenderFragment CardFooter { get; set; }

        [Parameter]
        public RenderFragment<TItem> CardHeader { get; set; }

        [Parameter]
        public TItem Item { get; set; }
    }
}
