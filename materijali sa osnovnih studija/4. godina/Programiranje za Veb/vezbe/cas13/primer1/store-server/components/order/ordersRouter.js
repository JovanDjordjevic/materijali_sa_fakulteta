const OrdersController = require('./ordersController');

class OrdersRouter {
    async get(req, res, next) {
        try {
            const controller = new OrdersController();
            const userId = req.query.userId;
            const authId = req.userId;

            if (userId !== authId) {
                const error = new Error("You are not authorized for this action!");
                error.status = 403;
                throw error;
            }

            const response = await controller.getOrdersByUserId(userId);
            res.status(200).json(response);
        } catch (err) {
            next(err);
        }
    }

    async getById(req, res, next) {
        try {
            const controller = new OrdersController();
            const orderId = req.params.id;
            const userId = req.query.userId;
            const authId = req.userId;

            if (userId !== authId) {
                const error = new Error("You are not authorized for this action!");
                error.status = 403;
                throw error;
            }
    
            const response = await controller.getOrderById(orderId);
            res.status(200).json(response);
        } catch (err) {
            next(err);
        }
    }

    async post(req, res, next) {
        try {
            const controller = new OrdersController();
            const userId = req.body.userId;
            const productsIds = req.body.productsIds;
            const authId = req.userId;

            if (userId !== authId) {
                const error = new Error("You are not authorized for this action!");
                error.status = 403;
                throw error;
            }
    
            const response = await controller.createOrder(userId, productsIds);
            res.status(200).json(response);
        } catch (err) {
            next(err);
        }
    }
}

module.exports = OrdersRouter;
